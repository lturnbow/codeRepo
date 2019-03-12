/******************************************************************************/
/*!
\file   ObjectAllocator.cpp
\author Lauren Turnbow
\brief
This file implements a memory manager
*/
/******************************************************************************/
#include "ObjectAllocator.h"
#include <string.h>
/******************************************************************************/
/*!
	\brief
		Creates the ObjectManager per the specified values. Throws an exception
		if the construction fails. (Memory allocation problem)

	\param ObjectSize
		Size of object to be set to private variable

	\param config
		config to be set to OAConfig struct
*/
/******************************************************************************/
ObjectAllocator::ObjectAllocator(size_t ObjectSize, const OAConfig& config)
{
	// Initializing private members
	oaconfig = config;
	oastats.ObjectSize_ = ObjectSize;
	FreeList_ = NULL;
	PageList_ = NULL;

	next_ = sizeof(void*);
	beginAlign_ = oaconfig.LeftAlignSize_;
	align_ = oaconfig.InterAlignSize_;
	header_ = oaconfig.HBlockInfo_.size_;
	pad_ = oaconfig.PadBytes_;
	objSize_ = oastats.ObjectSize_;

	// Setting alignments
	if (oaconfig.Alignment_ == 0) 
	{
		oaconfig.LeftAlignSize_ = 0;
		oaconfig.InterAlignSize_ = 0;
	}

	else
	{
		oaconfig.LeftAlignSize_ = (static_cast<unsigned int>(next_ + header_ + pad_)) % oaconfig.Alignment_;
		oaconfig.InterAlignSize_ = (static_cast<unsigned int>(objSize_ + (pad_ * 2) + header_)) % oaconfig.Alignment_;
	}

	allocate_new_page();
}

/******************************************************************************/
/*!
	\brief
		Take an object from the free list and give it to the client (simulates new).
		Throws an exception if the object can't be allocated. (Memory allocation
		problem)

	\param label

	\return
		Returns an unsigned char pointer
*/
/******************************************************************************/
void* ObjectAllocator::Allocate(const char *label)
{
	// If OA is to be disabled
	if (oaconfig.UseCPPMemManager_)
	{
		updateAllocations();
		unsigned char* obj = new unsigned char[sizeof(objSize_)];
		return obj;
	}

	unsigned char* free;
	
	// If there is nothing on the freelist, allocate a page
	if (!FreeList_)
		allocate_new_page();
	free = reinterpret_cast<unsigned char*>(FreeList_);
	FreeList_ = FreeList_->Next;

	
	updateAllocations();    // Updating the allocation statistics

	if (!oaconfig.DebugOn_) // Don't do anything else in function if debug isn't on
		return free;

	// Set the signatures of the allocated memory of the data portion
	memset(free, ALLOCATED_PATTERN, oastats.ObjectSize_);
	unsigned char* walkThru = reinterpret_cast<unsigned char*>(free);

	// External header
	if (oaconfig.HBlockInfo_.type_ == oaconfig.hbExternal)
	{
		walkThru -= header_ + pad_;  // Moving pointer to start of header block
		MemBlockInfo** temp = reinterpret_cast<MemBlockInfo**>(walkThru);
		*temp = new MemBlockInfo();  // Allocating the struct
		(*temp)->in_use = true;      // Setting the variables in the struct
		(*temp)->alloc_num = oastats.Allocations_;

		if (label)
		{
			size_t sizeofLabel = strlen(label) + 1;  // Length of label
			// Dynamically allocating space for the label
			(*reinterpret_cast<MemBlockInfo**>(walkThru))->label = new char[sizeofLabel];
			strcpy((*temp)->label, label);           // Copying label into allocated space
		}
		return free;
	}

	// Walking through the block and setting bytes to 1
	if (oaconfig.HBlockInfo_.type_ == oaconfig.hbBasic || oaconfig.HBlockInfo_.type_ == oaconfig.hbExtended)
	{
		walkThru -= (pad_ + 1);
		*walkThru = 1;           // Setting right byte to 1 in the header
		walkThru -= sizeof(int);
	}

	// Basic header
	if (oaconfig.HBlockInfo_.type_ == oaconfig.hbBasic)
		*reinterpret_cast<unsigned int*>(walkThru) = oastats.Allocations_;

	// Extended header
	else if (oaconfig.HBlockInfo_.type_ == oaconfig.hbExtended)
	{
		*reinterpret_cast<unsigned int*>(walkThru) = oastats.Allocations_;
		walkThru -= 2;
		// Incrementing number of times block has been looked at
		(*reinterpret_cast<unsigned short*>(walkThru))++;
	}

	return free;
}

/******************************************************************************/
/*!
	\brief
		Allocates another page of objects
*/
/******************************************************************************/
void ObjectAllocator::allocate_new_page(void)
{
	if (oastats.PageSize_ == 0)
	{
		// Getting the total page size
		oastats.PageSize_ = next_ + beginAlign_ + (align_ * (oaconfig.ObjectsPerPage_ - 1)) + 
			(header_ * (oaconfig.ObjectsPerPage_)) + (pad_ * (oaconfig.ObjectsPerPage_) * 2) 
			+ (objSize_ * oaconfig.ObjectsPerPage_);
	}

	// Throwing an exception of the max amount of pages has been reached
	if (oastats.PagesInUse_ >= oaconfig.MaxPages_ && oaconfig.MaxPages_ != 0)
		throw OAException(OAException::E_NO_PAGES, "allocate_new_page: Max pages reached");

	unsigned char* page;
	try 
	{
		page = new unsigned char[oastats.PageSize_]; // Allocating a page
	}
	catch (std::bad_alloc&) 
	{
		throw OAException(OAException::E_NO_MEMORY, "allocate_new_page: No system memory available.");
	}

	GenericObject* temp = PageList_;
	PageList_ = reinterpret_cast<GenericObject*>(page); // Setting pagelist to allocated page
	*PageList_ = GenericObject(temp);					// Placing next pointer at the start of the allocated page
	oastats.PagesInUse_++;
	unsigned char* walkThru = page;

	for (unsigned i = 0; i < oaconfig.ObjectsPerPage_; i++) {   // Going through objects and putting on the freelist
		if (i == 0)
			walkThru += next_ + beginAlign_ + header_ + pad_;
		else
			walkThru += objSize_ + (pad_ * 2) + align_ + header_;
		put_on_freelist(walkThru, true);
	}

	walkThru = page;           // Reset walker

	if (!oaconfig.DebugOn_)    // Don't do anything else in function if debug is not on      
		return;

	// Walking through first section of code before first object and setting align, header, and pad patterns
	walkThru += next_;         
	memset(walkThru, ALIGN_PATTERN, beginAlign_);
	walkThru += beginAlign_;
	memset(walkThru, 0x00, header_);
	walkThru += header_;
	memset(walkThru, PAD_PATTERN, pad_);
	walkThru += pad_;

	// Walking through objects on page and setting patterns for align, header, and pad
	for (unsigned i = 1; i <= oaconfig.ObjectsPerPage_; i++)
	{
		// Only do this section if it is the last object on list becuase the last object only has data and padding
		walkThru += objSize_;                 
		memset(walkThru, PAD_PATTERN, pad_);

		if (i != oaconfig.ObjectsPerPage_)
		{
			// Do this for every other object in the page that is not the beginning or end of the page
			walkThru += pad_;
			memset(walkThru, ALIGN_PATTERN, align_);
			walkThru += align_;
			memset(walkThru, 0x00, header_);
			walkThru += header_;
			memset(walkThru, PAD_PATTERN, pad_);
			walkThru += pad_;
		}
	}
}
/******************************************************************************/
/*!
	\brief
		Puts Object onto the free list

	\param Object
		Object to be put on the freelist

	\param func
		True if called from allocate_new_page, false if called from free
*/
/******************************************************************************/
void ObjectAllocator::put_on_freelist(void *Object, bool func)
{
	GenericObject* obj = reinterpret_cast<GenericObject*>(Object);
	GenericObject* freelist = FreeList_;
	GenericObject* pagelist = PageList_;
	unsigned char* walkThru;

	// If debug is off, create new generic object and put it on freelist and return
	if (!oaconfig.DebugOn_)
	{
		*obj = GenericObject(FreeList_);
		FreeList_ = obj;
		oastats.FreeObjects_++;
		return;
	}

	// Throw an exception if the object is already on the freelist
	while (freelist)
	{
		if (obj == freelist)
			throw OAException(OAException::E_MULTIPLE_FREE, "Multiple Free");
		freelist = freelist->Next;
	}

	bool misalign = true;
	while (pagelist)
	{
		walkThru = reinterpret_cast<unsigned char*>(pagelist);
		// Check if given object pointer is misaligned with where objects should go in the page
		walkThru += next_ + beginAlign_ + header_ + pad_;       // For first section of page
		for (unsigned i = 0; i < oaconfig.ObjectsPerPage_; i++)
		{
			if (i != 0)
				walkThru += objSize_ + (pad_ * 2) + align_ + header_;
			
			if (walkThru == reinterpret_cast<unsigned char*>(Object))
				misalign = false;
		}
		pagelist = pagelist->Next;
	}
	// Throw an exception if misaligned
	if (misalign)
		throw OAException(OAException::E_BAD_BOUNDARY, "Bad Boundary");

	// func is a boolean that tells where the put on freelist function was called from, either allocate new page or free 
	if (func)
		memset(Object, UNALLOCATED_PATTERN, oastats.ObjectSize_);
	else
		memset(Object, FREED_PATTERN, oastats.ObjectSize_);

	// Put object on freelist
	*obj = GenericObject(FreeList_);
	FreeList_ = obj;
	oastats.FreeObjects_++;
}

/******************************************************************************/
/*!
\brief
Calls the callback fn for each block still in use

\param fn
The DUMPCALLBACK function pointer that will be called on each block

\return
Returns the number of times memory has been dumped
*/
/******************************************************************************/
unsigned ObjectAllocator::DumpMemoryInUse(DUMPCALLBACK fn) const
{
	size_t beginning = next_ + beginAlign_ + header_ + pad_;
	size_t inner = objSize_ + (pad_ * 2) + align_ + header_;
	unsigned dumpCount = 0;   // Count how many times memory has been dumped
	GenericObject* pagelist = PageList_;

	while (pagelist)
	{
		unsigned char* walkThru = reinterpret_cast<unsigned char*>(pagelist);
		walkThru += beginning;
		// Going through page, dump memory if it is allocated
		for (unsigned i = 0; i < oaconfig.ObjectsPerPage_; i++)
		{
			if (i != 0)
				walkThru += inner;
			if (*walkThru == ALLOCATED_PATTERN)
			{
				// Call DUMPCALLBACK function pointer on allocated memory
				fn(walkThru, objSize_);   
				dumpCount++;
			}
		}
		pagelist = pagelist->Next;
	}

	return dumpCount;
}
/******************************************************************************/
/*!
\brief
Calls the callback fn for each block that is potentially corrupted

\param fn
The VALIDATECALLBACK function pointer that will be called on each block

\return
The number of corrupted blocks

*/
/******************************************************************************/
unsigned ObjectAllocator::ValidatePages(VALIDATECALLBACK fn) const
{
	// If debug is off or the pad size is 0, don't do anything else in the function
	if (!oaconfig.DebugOn_ || pad_ == 0)
		return 0;

	GenericObject* pagelist = PageList_;
	size_t beginning = next_ + beginAlign_ + header_ + pad_;
	size_t inner = objSize_ + (pad_ * 2) + align_ + header_;
	unsigned corruptCount = 0;  // Counting the number of objects that have corrupted memory

	while (pagelist)
	{
		unsigned char* walkThru = reinterpret_cast<unsigned char*>(pagelist);
		walkThru += beginning;
		for (unsigned i = 0; i < oaconfig.ObjectsPerPage_; i++)
		{
			// Looking for overflows, which show that memory has been corrupted
			bool overflow = false;
			if (i != 0)
				walkThru += inner;
			unsigned char* padWalk = walkThru;

			// Looping through pad bytes and seeing if there was an overflow
			overflow = loopThruValPad(padWalk, fn);

			// If there was an overflow, increment count and go to next object
			if (overflow)
			{
				corruptCount++;
				continue;
			}
			padWalk += objSize_ + pad_;

			overflow = loopThruValPad(padWalk, fn);

			if (overflow)
			{
				corruptCount++;
				continue;
			}
		}
		pagelist = pagelist->Next;
	}
	return corruptCount;
}

/******************************************************************************/
/*!
\brief
Returns an object to the free list for the client (simulates delete). Throws
an exception if the the object can't be freed. (Invalid object)

\param Object
The object to be freed
*/
/******************************************************************************/
void ObjectAllocator::Free(void*  Object)
{
	// If OA is disabled
	if (oaconfig.UseCPPMemManager_)
	{
		updateDeallocations();
		unsigned char* obj = reinterpret_cast<unsigned char*>(Object);
		delete[] obj;
		return;
	}

	// Putting object on freelist
	put_on_freelist(Object, false);
	updateDeallocations();

	// Don't do anything else in function if debug is off
	if (!oaconfig.DebugOn_)
		return;

	unsigned char* walkThru = reinterpret_cast<unsigned char*>(Object);

	// External header. Delete all allocated memory for memblockinfo struct
	if (oaconfig.HBlockInfo_.type_ == oaconfig.hbExternal)
	{
		walkThru -= header_ + pad_;
		if ((*reinterpret_cast<MemBlockInfo**>(walkThru))->label)
			delete[](*reinterpret_cast<MemBlockInfo**>(walkThru))->label;
		delete (*reinterpret_cast<MemBlockInfo**>(walkThru));
		memset(walkThru, 0x00, header_);
	}

	else if (oaconfig.HBlockInfo_.type_ == oaconfig.hbBasic || oaconfig.HBlockInfo_.type_ == oaconfig.hbExtended)
	{
		walkThru -= (pad_ + 1);
		*walkThru = 0;                                  // Setting right most byte to 0
		walkThru -= sizeof(int);
		*reinterpret_cast<unsigned int*>(walkThru) = 0; 
	}

	walkThru = reinterpret_cast<unsigned char*>(Object);
	loopThruPad(walkThru);    // Loop through padding, throwing exception if corrupted to validate padding
	walkThru = reinterpret_cast<unsigned char*>(Object);
	walkThru += objSize_ + pad_;
	loopThruPad(walkThru);    // Loop through padding, throwing exception if corrupted to validate padding
}

/******************************************************************************/
/*!
\brief
Destroys the ObjectManager (never throws)
*/
/******************************************************************************/
ObjectAllocator::~ObjectAllocator()
{
	while (PageList_)
	{
		// Going through page list and deleting pointer to pagelist
		unsigned char* toDelete = reinterpret_cast<unsigned char*>(PageList_);
		PageList_ = PageList_->Next;
		delete[] toDelete;
	}
}

/******************************************************************************/
/*!
	\brief
		Sets the debug state to on or off

	\param State
		The state that debug will set to
*/
/******************************************************************************/
void ObjectAllocator::SetDebugState(bool State)
{
	if (State == true)
		oaconfig.DebugOn_ = true;
	else if (State == false)
		oaconfig.DebugOn_ = false;
}

/******************************************************************************/
/*!
	\brief
		Returns a pointer to the internal free list

	\return
		Returns the freelist
*/
/******************************************************************************/
const void * ObjectAllocator::GetFreeList(void) const { return FreeList_; }

/******************************************************************************/
/*!
	\brief
		Returns a pointer to the internal page list

	\return
		Returns the pagelist
*/
/******************************************************************************/
const void * ObjectAllocator::GetPageList(void) const { return PageList_; }

/******************************************************************************/
/*!
	\brief
		Returns the configuration parameters

	\return
		Returns the config struct
*/
/******************************************************************************/
OAConfig ObjectAllocator::GetConfig(void) const { return oaconfig; }

/******************************************************************************/
/*!
	\brief
		Returns statistical parameters

	\returns
		Returns the stats struct
*/
/******************************************************************************/
OAStats ObjectAllocator::GetStats(void) const { return oastats; }
///////////////////////////////////////////////Helper Functions////////////////////////////////////////////
/******************************************************************************/
/*!
	\brief
		Updates allocation statistics
*/
/******************************************************************************/
void ObjectAllocator::updateAllocations(void)
{
	oastats.ObjectsInUse_++;
	oastats.Allocations_++;
	oastats.FreeObjects_--;

	// Updating the most objects if there are more objects in use
	if (oastats.ObjectsInUse_ > oastats.MostObjects_)
		oastats.MostObjects_ = oastats.ObjectsInUse_;
}

/******************************************************************************/
/*!
	\brief
		Loops through the padding, throws exception if block is corrupted

	\param	
		Pointer to walk through the pad
*/
/******************************************************************************/
void ObjectAllocator::loopThruPad(unsigned char* walkThru)
{
	for (unsigned i = 0; i < pad_; i++)
	{
		// Walking through the padding to check for corruption
		walkThru--;
		if ((*walkThru) != PAD_PATTERN)
			throw OAException(OAException::E_CORRUPTED_BLOCK, "Corrupted");
	}
}

/******************************************************************************/
/*!
	\brief
		Loops through the padding for the validation function

	\param padWalk
		Pointer to loop through the pad

	\param fn
		Function pointer that will be called on each loop

	\returns
	Returns is the pad has an overflow
*/
/******************************************************************************/
bool ObjectAllocator::loopThruValPad(unsigned char* padWalk, VALIDATECALLBACK fn) const
{
	bool overflow = false;
	for (unsigned j = 0; j < pad_; j++)
	{
		// Walking through the pad patern to check if there is an overflow. Validating
		// the padding if there is a corruption and setting overflow to true
		padWalk--;
		if (*padWalk != PAD_PATTERN)
		{
			fn(padWalk, objSize_);
			overflow = true;
			break;
		}
	}
	return overflow;
}

/******************************************************************************/
/*!
	\brief
		Updates the deallocation statistics
*/
/******************************************************************************/
void ObjectAllocator::updateDeallocations(void)
{
	oastats.Deallocations_++;
	oastats.ObjectsInUse_--;
}

/******************************************************************************/
/*!
\brief
Frees all empty pages 

\return
Number of pages free
*/
/******************************************************************************/
unsigned ObjectAllocator::FreeEmptyPages(void) { return 0; }

/******************************************************************************/
/*!
\brief
Returns true if FreeEmptyPages and alignments are implemented

\return
Returns if extra credit is being implemented
*/
/******************************************************************************/
bool ObjectAllocator::ImplementedExtraCredit(void) { return false; }

