# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.shortcuts import render
from .models import Table_GPS, Horizontal, Vertical, Conductivity, Compass
from django.http import HttpResponse, JsonResponse

from graphos.sources.simple import SimpleDataSource
from graphos.renderers.gchart import LineChart

import MySQLdb
import json

import poplib
import string, random
import StringIO, rfc822
import logging
import pdfkit

import reportlab
import csv
import math
from django.http import HttpResponse
from reportlab.pdfgen import canvas	

idList = []

# Create your views here.
def homepage(request):
	SERVER= "pop.gmail.com"   # This accesses the gmail server
	USER = "rockblock.digipen"
	PASSWORD = "CEdigipen1!"
	#connect to server
	logging.debug('connecting to ' + SERVER)
	server = poplib.POP3_SSL(SERVER)

	#login
	logging.debug('logging in')
	server.user(USER)
	server.pass_(PASSWORD)

	#list items on server
	logging.debug('listing emails')
	resp, items, octets = server.list()

	for i in range(0, len(items)):
		#download the first message in the list
		id, size = string.split(items[i])
		resp, text, octets = server.retr(id)
		
		
		#convert list to Message object
		text = string.join(text, "\n")
		file = StringIO.StringIO(text)
		message = rfc822.Message(file)

		#	continue
		print("------------------------------------")
		Date = message['Date']		# Reading the date and time in from the email
		Time = Date[17:25]
		Day = Date[12:16] + '-'
		Month = Date[8:11]
		if Month == 'Jan':			# Putting it in the format that MySQL takes
			Day += '01-' + Date[5:7]
		elif Month == 'Feb':
			Day += '02-' + Date[5:7]
		elif Month == 'Mar':
			Day += '03-' + Date[5:7]
		elif Month == 'Apr':
			Day += '04-' + Date[5:7]
		elif Month == 'May':
			Day += '05-' + Date[5:7]
		elif Month == 'Jun':
			Day += '06-' + Date[5:7]
		elif Month == 'Jul':
			Day += '07-' + Date[5:7]
		elif Month == 'Aug':
			Day += '08-' + Date[5:7]
		elif Month == 'Sept':
			Day += '09-' + Date[5:7]
		elif Month == 'Oct':
			Day += '10-' + Date[5:7]
		elif Month == 'Nov':
			Day += '11-' + Date[5:7]
		elif Month == 'Dec':
			Day += '12-' + Date[5:7]
			
		DayTime = Day + ' ' + Time				# DayTime
		
		if DayTime in idList:			# Using the date and time as the id for the list to not take duplicates
			continue


		idList.append(DayTime)			# Add id to list if it's not already in the list

		Subject = message['Subject']
		Sequence = Subject[8:11]				# Sequence
		
		contents = message.fp.read()		# Read the contents of the email, that includes all the data
		IMEIstart = contents.find('IMEI: ')	# Interpreting the header of the email
		IMEIfinish = IMEIstart + 6
		
		LATstart = contents.find('Iridium Latitude: ')  # Doing arithmetic to get the data without the labels
		LATfinish = LATstart + 18
		
		LONGstart = contents.find('Iridium Longitude: ')
		LONGfinish = LONGstart + 19
		
		SESSIONstart = contents.find('Iridium Session Status: ')
		SESSIONfinish = SESSIONstart + 24

		DATAstart = contents.find('Data:')
		DATAfinish = DATAstart + 6

		IMEI = contents[IMEIfinish:contents.find('MOMSN') - 1]
		Latitude = contents[LATfinish:LONGstart - 1]						#latitude
		Longitude = contents[LONGfinish:contents.find('Iridium CEP') - 1] 	#longitude
		Data = contents[DATAfinish:contents.find("\n\n\n")] 
		
		# Now getting all of the data from the packet and putting it into variables. Also converting them to int
		Version = int(Data[0:2],16)			#Version
		E = int(Data[2:4], 16)				#E
		GPSTime = int(Data[8:16], 16)		#GPS time
		pLatitude = int(Data[16:24],16)		#Latitude from packet
		pLongitude = int(Data[24:32], 16)	#Longitude from packet
		Altitude = int(Data[32:40], 16)		#Altitude
		Horiz1_1 = int(Data[40:44], 16)		#horiz1
		Horiz1_2 = int(Data[44:48], 16)
		Horiz1_3 = int(Data[48:52], 16)
		Horiz1_4 = int(Data[52:56], 16)
		Horiz1_5 = int(Data[56:60], 16)
		Horiz1_6 = int(Data[60:64], 16)
		Horiz1_7 = int(Data[64:68], 16)
		Horiz1_8 = int(Data[68:72], 16)
		Horiz1_9 = int(Data[72:76], 16)
		Horiz1_10 = int(Data[76:80], 16)
		Horiz1_11 = int(Data[80:84], 16)
		Horiz1_12 = int(Data[84:88], 16)
		
		Horiz2_1 = int(Data[88:92],16)		#horiz2
		Horiz2_2 = int(Data[92:96], 16)
		Horiz2_3 = int(Data[96:100], 16)
		Horiz2_4 = int(Data[100:104], 16)
		Horiz2_5 = int(Data[104:108], 16)
		Horiz2_6 = int(Data[108:112], 16)
		Horiz2_7 = int(Data[112:116], 16)
		Horiz2_8 = int(Data[116:120], 16)
		Horiz2_9 = int(Data[120:124], 16)
		Horiz2_10 = int(Data[124:128], 16)
		Horiz2_11 = int(Data[128:132], 16)
		Horiz2_12 = int(Data[132:136], 16)
		
		HorizD_1 = int(Data[136:140], 16)	#horizD
		HorizD_2 = int(Data[140:144], 16)
		HorizD_3 = int(Data[144:148], 16)
		HorizD_4 = int(Data[148:152], 16)
		HorizD_5 = int(Data[152:156], 16)
		HorizD_6 = int(Data[156:160], 16)
		HorizD_7 = int(Data[160:164], 16)
		HorizD_8 = int(Data[164:168], 16)
		HorizD_9 = int(Data[168:172], 16)
		HorizD_10 = int(Data[172:176], 16)
		HorizD_11 = int(Data[176:180], 16)
		HorizD_12 = int(Data[180:184], 16)
		
		Vert1 = int(Data[184:188], 16)		#vert1
		Vert2 = int(Data[188:192], 16)		#vert2
		VertD = int(Data[192:196], 16)		#vertD
		
		CompassX_1 = int(Data[196:200], 16)		#CompassX
		CompassX_2 = int(Data[200:204], 16)
		CompassX_3 = int(Data[204:208], 16)
		CompassX_4 = int(Data[208:212], 16)
		CompassX_5 = int(Data[212:216], 16)
		CompassX_6 = int(Data[216:220], 16)
		CompassX_7 = int(Data[220:224], 16)
		CompassX_8 = int(Data[224:228], 16)
		CompassX_9 = int(Data[228:232], 16)
		CompassX_10 = int(Data[232:236], 16)
		CompassX_11 = int(Data[236:240], 16)
		CompassX_12 = int(Data[240:244], 16)
		
		CompassY_1 = int(Data[244:248], 16)		#CompassY
		CompassY_2 = int(Data[248:252], 16)
		CompassY_3 = int(Data[252:256], 16)
		CompassY_4 = int(Data[256:260], 16)
		CompassY_5 = int(Data[260:264], 16)
		CompassY_6 = int(Data[264:268], 16)
		CompassY_7 = int(Data[268:272], 16)
		CompassY_8 = int(Data[272:276], 16)
		CompassY_9 = int(Data[276:280], 16)
		CompassY_10 = int(Data[280:284], 16)
		CompassY_11 = int(Data[284:288], 16)
		CompassY_12 = int(Data[288:292], 16)
		
		cVert1_1 = int(Data[292:296], 16)		#cVert1
		cVert1_2 = int(Data[296:300], 16)
		cVert1_3 = int(Data[300:304], 16)
		cVert1_4 = int(Data[304:308], 16)
		cVert1_5 = int(Data[308:312], 16)
		cVert1_6 = int(Data[312:316], 16)
		cVert1_7 = int(Data[316:320], 16)
		cVert1_8 = int(Data[320:324], 16)
		cVert1_9 = int(Data[324:328], 16)
		cVert1_10 = int(Data[328:332], 16)
		cVert1_11 = int(Data[332:336], 16)
		cVert1_12 = int(Data[336:340], 16)
		cVert1_13 = int(Data[340:344], 16)
		cVert1_14 = int(Data[344:348], 16)
		cVert1_15 = int(Data[348:352], 16)
		
		cVert2_1 = int(Data[352:356], 16)		#cVert2
		cVert2_2 = int(Data[356:360], 16)
		cVert2_3 = int(Data[360:364], 16)
		cVert2_4 = int(Data[364:368], 16)
		cVert2_5 = int(Data[368:372], 16)
		cVert2_6 = int(Data[372:376], 16)
		cVert2_7 = int(Data[376:380], 16)
		cVert2_8 = int(Data[380:384], 16)
		cVert2_9 = int(Data[384:388], 16)
		cVert2_10 = int(Data[388:392], 16)
		cVert2_11 = int(Data[392:396], 16)
		cVert2_12 = int(Data[396:400], 16)
		cVert2_13 = int(Data[400:404], 16)
		cVert2_14 = int(Data[404:408], 16)
		cVert2_15 = int(Data[408:412], 16)
		
		db = MySQLdb.connect(host="localhost", user="myprojectuser",passwd="raspberry", db="myproject") # Accessing the database
		cur = db.cursor()
		cur.execute('SELECT * FROM myproject.tutorialapp_table_gps')
		cur.execute("""INSERT INTO tutorialapp_table_gps VALUES (%s, %s, %s, %s, %s, %s, %s)""", (DayTime, Version, E, Sequence, Latitude, Longitude, Altitude)) # Insert the data into each table
		db.commit()
		cur.execute("""INSERT INTO tutorialapp_horizontal VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, \
					%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s)""", (DayTime, Horiz1_1, Horiz1_2, Horiz1_3, Horiz1_4, Horiz1_5, Horiz1_6, Horiz1_7, Horiz1_8, Horiz1_9, 
					Horiz1_10, Horiz1_11, Horiz1_12, Horiz2_1, Horiz2_2, Horiz2_3, Horiz2_4, Horiz2_5, Horiz2_6, Horiz2_7, Horiz2_8, Horiz2_9, Horiz2_10, Horiz2_11,
					Horiz2_12, HorizD_1, HorizD_2, HorizD_3, HorizD_4, HorizD_5, HorizD_6, HorizD_7, HorizD_8, HorizD_9, HorizD_10, HorizD_11, HorizD_12))
		db.commit()
		cur.execute("""INSERT INTO tutorialapp_vertical VALUES (%s, %s, %s, %s)""", (DayTime, Vert1, Vert2, VertD))
		db.commit()
		cur.execute("""INSERT INTO tutorialapp_compass VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s)""", (DayTime, CompassX_1, CompassX_2, CompassX_3, CompassX_4, CompassX_5, CompassX_6, CompassX_7, CompassX_8, CompassX_9,
					CompassX_10, CompassX_11, CompassX_12, CompassY_1, CompassY_2, CompassY_3, CompassY_4, CompassY_5, CompassY_6, CompassY_7, CompassY_8, CompassY_9, 
					CompassY_10, CompassY_11, CompassY_12))
		db.commit()
		
		#Calculate time constant
		numpoints = 15
		time = [4,8,12,16,20,24,28,32,36,40,44,48,52,56,60]
		cVert1Voltage = [cVert1_1,cVert1_2,cVert1_3,cVert1_4,cVert1_5,cVert1_6,cVert1_7,cVert1_8,cVert1_9,cVert1_10,cVert1_11,cVert1_12,cVert1_13,cVert1_14,cVert1_15]
		cVert2Voltage = [cVert2_1,cVert2_2,cVert2_3,cVert2_4,cVert2_5,cVert2_6,cVert2_7,cVert2_8,cVert2_9,cVert2_10,cVert2_11,cVert2_12,cVert2_13,cVert2_14,cVert2_15]
		x2y1 = 0.0
		ylny1 = 0.0
		xy1 = 0.0
		xylny1 = 0.0
		y1 = 0.0
		x2y2 = 0.0
		ylny2 = 0.0
		xy2 = 0.0
		xylny2 = 0.0
		y2 = 0.0

		for i in range(0, numpoints):
			x2y1 += pow(time[i], 2.0) * cVert1Voltage[i]
			x2y2 += pow(time[i], 2.0) * cVert2Voltage[i]
			
		for i in range(0, numpoints):
			ylny1 += cVert1Voltage[i] * math.log(cVert1Voltage[i])
			ylny2 += cVert2Voltage[i] * math.log(cVert2Voltage[i])

		for i in range(0, numpoints):
			xy1 += time[i] * cVert1Voltage[i]
			xy2 += time[i] * cVert2Voltage[i]
			
		for i in range(0, numpoints):
			xylny1 += time[i] * cVert1Voltage[i] * math.log(cVert1Voltage[i])
			xylny2 += time[i] * cVert2Voltage[i] * math.log(cVert2Voltage[i])
			
		for i in range(0, numpoints):
			y1 += cVert1Voltage[i]
			y2 += cVert2Voltage[i]

		b1 = (y1 * xylny1 - xy1 * ylny1) / (y1 * x2y1 - pow(xy1, 2))
		b2 = (y2 * xylny2 - xy2 * ylny2) / (y2 * x2y2 - pow(xy2, 2))
		TimeConstant1 = -1 / b1
		TimeConstant2 = -1 / b2
		TimeConstant = (TimeConstant1 + TimeConstant2) / 2.0

		cur.execute("""INSERT INTO tutorialapp_conductivity VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, \
					%s, %s, %s, %s, %s, %s, %s)""", (DayTime, cVert1_1, cVert1_2, cVert1_3, cVert1_4, cVert1_5, cVert1_6, cVert1_7, cVert1_8, cVert1_9, cVert1_10, cVert1_11,
					cVert1_12, cVert1_13, cVert1_14, cVert1_15, cVert2_1, cVert2_2, cVert2_3, cVert2_4, cVert2_5, cVert2_6, cVert2_7, cVert2_8, cVert2_9, cVert2_10,
					cVert2_11, cVert2_12, cVert2_13, cVert2_14, cVert2_15, TimeConstant))
		db.commit()
		db.close()
	return render(request, 'tutorial/homepage.html')
	
def tables(request):
	data = Table_GPS.objects.all()  # This returns all of the tables so I can put them all onto one page at external_ip:5000/tables/ in site view
	data1 = Vertical.objects.all()
	data2 = Horizontal.objects.all()
	data3 = Compass.objects.all()
	data4 = Conductivity.objects.all()
	return render(request, 'tutorial/tables.html', {'data': data, 'data1': data1, 'data2': data2, 'data3': data3, 'data4': data4})

########################################################################
def mapPlot(request):    # Change to google maps
	data = [
				['Daytime', 'Longitude', 'Latitude']  # create a list to hold the column names and data for the axis names
		   ]
	
	db = MySQLdb.connect(host="localhost", user="myprojectuser",passwd="raspberry", db="myproject") # Access the database to get all the current data
	cur = db.cursor()
	cur.execute('SELECT * FROM myproject.tutorialapp_table_gps')
	for row in cur.fetchall(): # going through each row
		l = []
		l.append(row[0]) # append each row to the data, only get the columns that we want
		l.append(row[4])
		l.append(row[5])
		data.append(l)
		
	db.close()
	data_source = SimpleDataSource(data=data)
	chart = LineChart(data_source, options={'title': "Coordinates"}) # Creating a line chart
	
	context = {'chart': chart}
	return render(request, 'tutorial/mapPlot.html', context)	# rendering the chart when a request has gone through for this page, and using the mapPlot.html to render it
	
########################################################################
def altitude(request):
	data = [
				['DayTime', 'Altitude']
		   ]
		   
	db = MySQLdb.connect(host="localhost", user="myprojectuser",passwd="raspberry", db="myproject")
	cur = db.cursor()
	cur.execute('SELECT * FROM myproject.tutorialapp_table_gps')
	for row in cur.fetchall():
		l = []
		l.append(row[0])
		l.append(row[6])
		data.append(l)
		
	db.close()
	data_source = SimpleDataSource(data=data)
	chart = LineChart(data_source, options={'title': "Altitude"})
	context = {'chart': chart}
	return render(request, 'tutorial/altitude.html', context)
	
########################################################################
def horizontal(request):
	
	data = [
				['DayTime', 'Horizontal1', 'Horizontal2', 'HorizontalDelta']
		   ]
		   
	db = MySQLdb.connect(host="localhost", user="myprojectuser",passwd="raspberry", db="myproject")
	cur = db.cursor()
	cur.execute('SELECT * FROM myproject.tutorialapp_horizontal')
	for row in cur.fetchall():
		l = []
		l.append(row[0])
		
		s = 0.0						# Averaging the data, not plotting all 12 points for the Horiz1, Horiz2, and HorizD
		for i in range(1,12 + 1):
			s += row[i]
		l.append(s / 12.0)
		
		s1 = 0.0
		for i in range(13,24 + 1):
			s1 += row[i]
		l.append(s1 / 12.0)
		
		s2 = 0.0
		for i in range(24,36 + 1):
			s2 += row[i]
		l.append(s2 / 12.0)

		data.append(l)
		
	db.close()
	data_source = SimpleDataSource(data=data)
	chart = LineChart(data_source, options={'title': "Horizontal"})
	
	context = {'chart': chart}
	return render(request, 'tutorial/horizontal.html', context)
	
########################################################################
def vertical(request):
	data = [
				['DayTime', 'Vertical1', 'Vertical2', 'Vertical3']
		   ]
		   
	db = MySQLdb.connect(host="localhost", user="myprojectuser",passwd="raspberry", db="myproject")
	cur = db.cursor()
	cur.execute('SELECT * FROM myproject.tutorialapp_vertical')
	for row in cur.fetchall():
		l = []
		l.append(row[0])
		l.append(row[1])
		l.append(row[2])
		l.append(row[3])
		data.append(l)
		
	db.close()
	data_source = SimpleDataSource(data=data)
	chart = LineChart(data_source, options={'title': "Vertical"})
	context = {'chart': chart}
	return render(request, 'tutorial/vertical.html', context)
	
########################################################################
def compass(request):
	
	data = [
				['DayTime', 'CompassX', 'CompassY']
		   ]
		   
	db = MySQLdb.connect(host="localhost", user="myprojectuser",passwd="raspberry", db="myproject")
	cur = db.cursor()
	cur.execute('SELECT * FROM myproject.tutorialapp_compass')
	for row in cur.fetchall():
		l = []
		l.append(row[0])
		
		s = 0.0
		for i in range(1,12 + 1):
			s += row[i]
		l.append(s / 12.0)
		
		s1 = 0.0
		for i in range(13,24 + 1):
			s1 += row[i]
		l.append(s1 / 12.0)
	
		data.append(l)
		
	db.close()
	data_source = SimpleDataSource(data=data)
	chart = LineChart(data_source, options={'title': "Compass"})
	
	context = {'chart': chart}
	return render(request, 'tutorial/compass.html', context)
	
########################################################################
def conductivity(request):
	
	data = [
				['DayTime', 'ConductivityProbe1', 'ConductivityProbe2']
		   ]
		   
	db = MySQLdb.connect(host="localhost", user="myprojectuser",passwd="raspberry", db="myproject")
	cur = db.cursor()
	cur.execute('SELECT * FROM myproject.tutorialapp_conductivity')
	for row in cur.fetchall():
		l = []
		l.append(row[0])
		
		s = 0.0
		for i in range(1, 15 + 1):
			s += row[i]
		l.append(s / 15.0)
		
		s1 = 0.0
		for i in range(16, 30 + 1):
			s1 += row[i]
		l.append(s1 / 15.0)
		
		data.append(l)
		
	db.close()
	data_source = SimpleDataSource(data=data)
	chart = LineChart(data_source, options={'title': "Conductivity"})
	context = {'chart': chart}
	return render(request, 'tutorial/conductivity.html', context)
########################################################################
def _pdf(request):		# Creating the PDF, having to draw it one by one
	response = HttpResponse(content_type='application/pdf')
	response['Content-Disposition'] = 'filename="tables_pdf.pdf" '
	p = canvas.Canvas(response)
	p.drawString(20, 800, "GPS")  # Have to keep track of the x and y coordinates of where to put the text on the pdf
	p.drawString(20, 780, "DayTime                         Version     Error     Sequence     Latitude       Longitude            Altitude")
	db = MySQLdb.connect(host="localhost", user="myprojectuser", passwd="raspberry", db="myproject")
	cur = db.cursor()
	#GPS Table
	cur.execute('SELECT * FROM myproject.tutorialapp_table_gps') # Going through each table to get the current data
	i = 760
	for row in cur.fetchall():
		l = ""
		l += str(row[0]) + "          " + str(row[1]) + "            " + str(row[2]) + "             " + str(row[3]) + "          " \
			+ str(row[4]) + "      " + str(row[5]) + "          " + str(row[6])
		p.drawString(20, i, str(l))
		i -= 20
	#Horizontal Table
	i -= 40
	p.drawString(20, i, "Horizontal")
	i -= 20
	p.drawString(20, i, "DayTime                              Horiz1             Horiz2                           HorizD")
	i -= 20
	cur.execute('SELECT * FROM myproject.tutorialapp_horizontal')
	for row in cur.fetchall():
		l = ""
		l += str(row[0]) + "          "
		
		s = 0.0
		for j in range(1,12 + 1):	#Averaging the data, for the PDF 36 rows won't fit in the PDF
			s += row[j]
		s1 = 0.0
		for j in range(13,24 + 1):
			s1 += row[j]
		s2 = 0.0
		for j in range(24,36 + 1):
			s2 += row[j]
		
		l += str(s / 12.0) + "          " + str(s1 / 12.0) + "          " + str(s2 / 12.0)
		p.drawString(20, i, str(l))
		i -= 20
	#Vertical Table
	i -= 40
	p.drawString(20, i, "Vertical")
	i -= 20
	p.drawString(20, i, "DayTime                              Vert1          Vert2           VertD")
	i -= 20
	cur.execute('SELECT * FROM myproject.tutorialapp_vertical')
	for row in cur.fetchall():
		l = ""
		l += str(row[0]) + "          " + str(row[1]) + "          " + str(row[2]) + "          " + str(row[3])
		p.drawString(20, i, str(l))
		i -= 20 
	#Compass Table
	i -= 40
	p.drawString(20, i, "Compass")
	i -= 20
	p.drawString(20, i, "DayTime                       CompassX    CompassY")
	i -= 20
	cur.execute('SELECT * FROM myproject.tutorialapp_compass')
	for row in cur.fetchall():
		l = ""
		l += str(row[0]) + "    "
		s = 0.0
		for j in range(1,12 + 1):
			s += row[j]
		s1 = 0.0
		for j in range(13,24 + 1):
			s1 += row[j]
		l += str(s / 12.0) + "            " + str(s1 / 12.0)
		p.drawString(20, i, str(l))
		i -= 20
	#Conductivity Table
	i -= 40
	p.drawString(20, i, "Conductivity")
	i -= 20
	p.drawString(20, i, "DayTime                       cVert1        cVert2       TimeConstant")
	i -= 20
	cur.execute('SELECT * FROM myproject.tutorialapp_conductivity')
	for row in cur.fetchall():
		l = ""
		l += str(row[0]) + "     "
		s = 0.0
		for j in range(1, 15 + 1):
			s += row[j]
		s1 = 0.0
		for j in range(16, 30 + 1):
			s1 += row[j]
		l += str(s / 15.0) + "    " + str(s1 / 15.0) + "      " + str(row[31])
		p.drawString(20, i, str(l))
		i -= 20
		
	db.close()
	p.showPage()  # Show the page on the screen, it can be downloaded from there 
	p.save()
	return response
########################################################################
def _csv(request):	# Writing the csv row by row, 
	response = HttpResponse(content_type='text/csv')
	response['Content-Disposition'] = 'filename="tables_csv.csv" '
	
	writer = csv.writer(response)	# A csv object to write each row
	db = MySQLdb.connect(host="localhost", user="myprojectuser", passwd="raspberry", db="myproject") # Opening the database to access the current data
	cur = db.cursor()
	#GPS Table
	cur.execute('SELECT * FROM myproject.tutorialapp_table_gps')
	writer.writerow(['GPS'])
	writer.writerow(['DayTime', 'Version', 'Error', 'Sequence', 'Latitude', 'Longitude', 'Altitude'])
	for row in cur.fetchall():
		writer.writerow([row[0], row[1], row[2], row[3], row[4], row[5], row[6]])
	writer.writerow([])
	#Horizontal Table
	cur.execute('SELECT * FROM myproject.tutorialapp_horizontal')
	writer.writerow(['Horizontal'])
	writer.writerow(['DayTime', 'Horiz1_1', 'Horiz1_2', 'Horiz1_3', 'Horiz1_4', 'Horiz1_5', 'Horiz1_6', 
		'Horiz1_7', 'Horiz1_8', 'Horiz1_9', 'Horiz1_10', 'Horiz1_11', 'Horiz1_12', 'Horiz2_1', 'Horiz2_2', 
		'Horiz2_3', 'Horiz2_4', 'Horiz2_5', 'Horiz2_6', 'Horiz2_7', 'Horiz2_8', 'Horiz2_9', 'Horiz2_10',  
		'Horiz2_11', 'Horiz2_12', 'HorizD_1', 'HorizD_2', 'HorizD_3', 'HorizD_4', 'HorizD_5', 'HorizD_6', 
		'HorizD_7', 'HorizD_8', 'HorizD_9', 'HorizD_10', 'HorizD_11', 'HorizD_12'])
	for row in cur.fetchall(): # Write all rows and columns. Includes all data for further calculations
		writer.writerow([row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7], row[8], row[9], row[10],
			row[11], row[12], row[13], row[14], row[15], row[16], row[17], row[18], row[19], row[20], row[21], 
			row[22], row[23], row[24], row[25], row[26], row[27], row[28], row[29], row[30], row[31], row[32],
			row[33], row[34], row[35], row[36]])
	writer.writerow([])
	#Vertical Table
	cur.execute('SELECT * FROM myproject.tutorialapp_vertical')
	writer.writerow(['Vertical'])
	writer.writerow(['DayTime', 'Vert1', 'Vert2', 'VertD'])
	for row in cur.fetchall():
		writer.writerow([row[0], row[1], row[2], row[3]])
	writer.writerow([])
	#Compass Table
	cur.execute('SELECT * FROM myproject.tutorialapp_compass')
	writer.writerow(['Compass'])
	writer.writerow(['DayTime', 'CompassX_1', 'CompassX_2', 'CompassX_3', 'CompassX_4', 'CompassX_5', 'CompassX_6', 
		'CompassX_7', 'CompassX_8', 'CompassX_9', 'CompassX_10', 'CompassX_11', 'CompassX_12', 'CompassY_1', 'CompassY_2',
		'CompassY_3', 'CompassY_4', 'CompassY_5', 'CompassY_6', 'CompassY_7', 'CompassY_8', 'CompassY_9', 'CompassY_10', 
		'CompassY_11', 'CompassY_12'])
	for row in cur.fetchall():
		writer.writerow([row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7], row[8], row[9], row[10],
			row[11], row[12], row[13], row[14], row[15], row[16], row[17], row[18], row[19], row[20], row[21], 
			row[22], row[23], row[24]])
	writer.writerow([])
	#Conductivity Table
	cur.execute('SELECT * FROM myproject.tutorialapp_conductivity')
	writer.writerow(['Conductivity'])
	writer.writerow(['DayTime', 'cVert1_1', 'cVert1_2', 'cVert1_3', 'cVert1_4', 'cVert1_5', 'cVert1_6', 'cVert1_7',
		'cVert1_8', 'cVert1_9', 'cVert1_10', 'cVert1_11', 'cVert1_12', 'cVert1_13', 'cVert1_14', 'cVert1_15', 
		'cVert2_1', 'cVert2_2', 'cVert2_3', 'cVert2_4', 'cVert2_5', 'cVert2_6', 'cVert2_7', 'cVert2_8', 'cVert2_9', 
		'cVert2_10', 'cVert2_11', 'cVert2_12', 'cVert2_13', 'cVert2_14', 'cVert2_15', 'TimeConstant'])
	for row in cur.fetchall():
		writer.writerow([row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7], row[8], row[9], row[10],
			row[11], row[12], row[13], row[14], row[15], row[16], row[17], row[18], row[19], row[20], row[21], 
			row[22], row[23], row[24], row[25], row[26], row[27], row[28], row[29], row[30], row[31]])
	db.close()
	
	return response
	
