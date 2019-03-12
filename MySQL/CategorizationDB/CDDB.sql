-- Author: Lauren Turnbow
use mysql;
-- Creating Genre table -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
CREATE TABLE Genre (GenreName varchar(12) PRIMARY KEY);
INSERT INTO Genre (GenreName) VALUES ('Rock');
INSERT INTO Genre (GenreName) VALUES ('Classical');
INSERT INTO Genre (GenreName) VALUES ('Pop');
INSERT INTO Genre (GenreName) VALUES ('Jazz');
INSERT INTO Genre (GenreName) VALUES ('Rap');
SELECT * FROM Genre;

-- Creating Listener table -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
CREATE TABLE Listener (ListenerName varchar(10), Address varchar(30), Birthday DATE, PRIMARY KEY (ListenerName, Address));
INSERT INTO Listener (ListenerName, Address, Birthday) VALUES ('Joe', '123 Maple Drive', '1990-01-02');
INSERT INTO Listener (ListenerName, Address, Birthday) VALUES ('Bob', '456 Oak Lane', '1992-04-27');
INSERT INTO Listener (ListenerName, Address, Birthday) VALUES ('Katie', '789 Beech Street', '1991-08-15');
INSERT INTO Listener (ListenerName, Address, Birthday) VALUES ('Crystal', '246 Pine Boulevard', '1996-12-16');
INSERT INTO Listener (ListenerName, Address, Birthday) VALUES ('Elliot', '357 Walnut Lane', '1995-11-04');
SELECT * FROM Listener;

-- Creating Box table -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
CREATE TABLE Box (BoxNum int PRIMARY KEY, Color varchar(10));
INSERT INTO Box (BoxNum, Color) VALUES (1, 'Red');
INSERT INTO Box (BoxNum, Color) VALUES (2, 'Yellow');
INSERT INTO Box (BoxNum, Color) VALUES (3, 'Blue');
INSERT INTO Box (BoxNum, Color) VALUES (4, 'Green');
INSERT INTO Box (BoxNum, Color) VALUES (5, 'Orange');
SELECT * FROM Box;

-- Creating CD table -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
CREATE TABLE CD (Title varchar(100), ReleaseDate DATE, RecordLabel varchar(50), NumTracks int, PRIMARY KEY(Title, ReleaseDate, RecordLabel));
INSERT INTO CD (Title, ReleaseDate, RecordLabel, NumTracks) VALUES ('Dark Side of the Moon', '1973-03-01', 'Harvest Records', 10);
INSERT INTO CD (Title, ReleaseDate, RecordLabel, NumTracks) VALUES ('Led Zeppelin IV', '1971-11-08', 'Atlantic Records', 8);
INSERT INTO CD (Title, ReleaseDate, RecordLabel, NumTracks) VALUES ('Beethoven Greatest Hits', '1991-09-06', 'RCA', 7);
INSERT INTO CD (Title, ReleaseDate, RecordLabel, NumTracks) VALUES ('...Baby One More Time', '1999-01-12', 'Jive Records', 11);
INSERT INTO CD (Title, ReleaseDate, RecordLabel, NumTracks) VALUES ('Now Thats What I Call Music 64', '2017-11-03', 'Sony Music', 11);
INSERT INTO CD (Title, ReleaseDate, RecordLabel, NumTracks) VALUES ('Kind of Blue', '1959-08-17', 'Columbia Records', 5);
INSERT INTO CD (Title, ReleaseDate, RecordLabel, NumTracks) VALUES ('Recovery', '2010-06-18', 'Interscope Records', 16);
SELECT * FROM CD;

-- Creating Song table -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
CREATE TABLE Song (SongName varchar(100), Composer varchar(50), Length TIME, TrackNum int, PRIMARY KEY (SongName, Composer));
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Fate', 'Beethoven', '00:33:43', 1);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Ruins of Athens', 'Beethoven', '00:08:22', 2);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Moonlight', 'Beethoven', '00:07:35', 3);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Fur Elise', 'Beethoven', '00:03:36', 4);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Ode to Joy', 'Beethoven', '00:26:46', 5);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Eroica', 'Beethoven', '00:52:02', 6);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Choral Fantasy', 'Beethoven', '00:21:13', 7);

INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Speak to Me', 'Nick Mason', '00:01:30', 1);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Breathe', 'Roger Waters', '00:02:43', 2);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('On the Run', 'Roger Waters', '00:03:30', 3);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Time', 'Nick Mason', '00:06:53', 4);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('The Great Gig in the Sky', 'Richard Wright', '00:04:15', 5);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Money', 'Roger Waters', '00:06:30', 6);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Us and Them', 'Roger Waters', '00:07:51', 7);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Any Color You Like', 'David Gilmour', '00:03:24', 8);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Brain Damage', 'Roger Waters', '00:03:50', 9);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Eclipse', 'Roger Waters', '00:02:53', 10);

INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Black Dog', 'Jimmy Page', '00:04:54', 1);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Rock and Roll', 'Jimmy Page', '00:03:40', 2);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('The Battle of Evermore', 'Jimmy Page', '00:05:51', 3);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Stairway to Heaven', 'Jimmy Page', '00:08:02', 4);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Misty Mountain Hop', 'Jimmy Page', '00:04:38', 5);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Four Sticks', 'Jimmy Page', '00:04:44', 6);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Going to California', 'Jimmy Page', '00:03:31', 7);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('When the Levee Breaks', 'Jimmy Page', '00:07:07', 8);

INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('...Baby One More Time', 'Max Martin', '00:03:31', 1);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('You Drive Me Crazy', 'Jorgen Elofsson', '00:03:18', 2);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Sometimes', 'Jorgen Elofsson', '00:04:05', 3);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Soda Pop', 'Mikey Bassie', '00:03:20', 4);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Born to Make You Happy', 'Kristian Lundin', '00:04:03', 5);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('From the Bottom of My Broken Heart', 'Eric Foster White', '00:05:12', 6);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('I Will Be There', 'Max Martin', '00:03:53', 7);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('I Will Still Love You', 'Eric Foster White', '00:04:03', 8);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Thinkin About You', 'Mikey Bassie', '00:03:34', 9);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('E-Mail My Heart', 'Eric Foster White', '00:03:43', 10);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('The Beat Goes On', 'Sonny Bono', '00:03:43', 11);

INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Attention', 'Charlie Puth', '00:03:21', 1);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Despacito', 'Luis Rodriguez', '00:04:18', 2);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Theres Nothing Holdin Me Back', 'Shawn Mendes', '00:03:54', 3);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('What About Us', 'Pink', '00:04:32', 4);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Strip That Down', 'Liam Payne', '00:04:18', 5);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Feels', 'Adam Wiles', '00:03:14', 6);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('What Lovers Do', 'Adam Levine', '00:03:57', 7);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Unforgettable', 'Karim Kharbouch', '00:03:02', 8);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Redbone', 'Donald Glover', '00:05:39', 9);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Praying', 'Kesha Sebert', '00:04:03', 10);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Make Me', 'Britney Spears', '00:04:38', 11);

INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('So What', 'Miles Davis', '00:09:04', 1);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Freddie Freeloader', 'Miles Davis', '00:09:34', 2);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Blue in Green', 'Miles Davis', '00:05:27', 3);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('All Blues', 'Miles Davis', '00:11:33', 4);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Flamenco Sketches', 'Miles Davis', '00:09:26', 5);

INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Cold Wind Blows', 'Marshall Mathers', '00:05:03', 1);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Talkin 2 Myself', 'Marshall Mathers', '00:05:00', 2);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('On Fire', 'Marshall Mathers', '00:03:33', 3);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Wont Back Down', 'Marshall Mathers', '00:04:25', 4);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('W.T.P.', 'Marshall Mathers', '00:03:58', 5);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Going Through Changes', 'Marshall Mathers', '00:04:58', 6);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Not Afraid', 'Marshall Mathers', '00:04:10', 7);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Seduction', 'Marshall Mathers', '00:04:35', 8);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('No Love', 'Marshall Mathers', '00:05:00', 9);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Space Bound', 'Marshall Mathers', '00:04:38', 10);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Cinderella Man', 'Marshall Mathers', '00:04:39', 11);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('25 to Life', 'Marshall Mathers', '00:04:01', 12);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('So Bad', 'Marshall Mathers', '00:05:25', 13);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Almost Famous', 'Marshall Mathers', '00:04:52', 14);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Love the Way You Lie', 'Marshall Mathers', '00:04:23', 15);
INSERT INTO Song (SongName, Composer, Length, TrackNum) VALUES ('Youre Never Over', 'Marshall Mathers', '00:05:05', 16);

SELECT * FROM Song;

-- Creating Artist table -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
CREATE TABLE Artist (ArtistName varchar(30) PRIMARY KEY, Homepage varchar(100), Hometown varchar(50));
INSERT INTO Artist (ArtistName, Homepage, Hometown) VALUES ('Pink Floyd', 'www.pinkfloyd.com', 'London');
INSERT INTO Artist (ArtistName, Homepage, Hometown) VALUES ('Led Zeppelin', 'www.ledzeppelin.com', 'London');
INSERT INTO Artist (ArtistName, Homepage, Hometown) VALUES ('Beethoven', 'www.beethoven.com', 'Bonn');
INSERT INTO Artist (ArtistName, Homepage, Hometown) VALUES ('Britney Spears', 'www.britneyspears.com', 'Kentwood');
INSERT INTO Artist (ArtistName, Homepage, Hometown) VALUES ('Eminem', 'www.eminem.com', 'Saint Joseph');
INSERT INTO Artist (ArtistName, Homepage, Hometown) VALUES ('Charlie Puth', 'www.charlieputh.com', 'Rumson');
INSERT INTO Artist (ArtistName, Homepage, Hometown) VALUES ('Luis Fonsi', 'www.luisfonsi.com', 'San Juan');
INSERT INTO Artist (ArtistName, Homepage, Hometown) VALUES ('Shawn Mendes', 'www.shawnmendes.com', 'Toronto');
INSERT INTO Artist (ArtistName, Homepage, Hometown) VALUES ('Pink', 'www.pink.com', 'Doylestown');
INSERT INTO Artist (ArtistName, Homepage, Hometown) VALUES ('Liam Payne', 'www.liampayne.com', 'Wolverhampton');
INSERT INTO Artist (ArtistName, Homepage, Hometown) VALUES ('Calvin Harris', 'www.calvinharris.com', 'Dumfries');
INSERT INTO Artist (ArtistName, Homepage, Hometown) VALUES ('Maroon 5', 'www.maroon5.com', 'Los Angeles');
INSERT INTO Artist (ArtistName, Homepage, Hometown) VALUES ('French Montana', 'www.frenchmontana.com', 'Rabat');
INSERT INTO Artist (ArtistName, Homepage, Hometown) VALUES ('Miles Davis', 'www.milesdavis.com', 'Alton');
INSERT INTO Artist (ArtistName, Homepage, Hometown) VALUES ('Childish Gambino', 'www.childishgambino.com', 'Edwards AF Base');
INSERT INTO Artist (ArtistName, Homepage, Hometown) VALUES ('Kesha', 'www.kesha.com', 'Los Angeles');

SELECT * FROM Artist;

-- Creating Instrument table -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
CREATE TABLE Instrument (InstrumentName varchar(15) PRIMARY KEY, Family varchar(20));
INSERT INTO Instrument (InstrumentName, Family) VALUES ('Guitar', 'String');
INSERT INTO Instrument (InstrumentName, Family) VALUES ('Drums', 'Percussion');
INSERT INTO Instrument (InstrumentName, Family) VALUES ('Voice', 'Vocal');
INSERT INTO Instrument (InstrumentName, Family) VALUES ('Bass', 'String');
INSERT INTO Instrument (InstrumentName, Family) VALUES ('Piano', 'Stuck String');
INSERT INTO Instrument (InstrumentName, Family) VALUES ('Trumpet', 'Brass');
SELECT * FROM Instrument;

-- ********************************************* Relationships **********************************************
-- Creating Case table -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
CREATE TABLE Cases (NumCDs int, BoxNum int, Title varchar(50), ReleaseDate DATE, RecordLabel varchar(30), 
					FOREIGN KEY(BoxNum) REFERENCES Box(BoxNum) ON DELETE CASCADE ON UPDATE CASCADE, 
                    FOREIGN KEY (Title, ReleaseDate, RecordLabel) REFERENCES CD (Title, ReleaseDate, RecordLabel));
INSERT INTO Cases (NumCDs, BoxNum, Title, ReleaseDate, RecordLabel) VALUES (1, 1, 'Beethoven Greatest Hits', '1991-09-06', 'RCA');
INSERT INTO Cases (NumCDs, BoxNum, Title, ReleaseDate, RecordLabel) VALUES (1, 1, '...Baby One More Time', '1999-01-12', 'Jive Records');
INSERT INTO Cases (NumCDs, BoxNum, Title, ReleaseDate, RecordLabel) VALUES (2, 2, 'Dark Side of the Moon', '1973-03-01', 'Harvest Records');
INSERT INTO Cases (NumCDs, BoxNum, Title, ReleaseDate, RecordLabel) VALUES (1, 3, 'Now Thats What I Call Music 64', '2017-11-03', 'Sony Music');
INSERT INTO Cases (NumCDs, BoxNum, Title, ReleaseDate, RecordLabel) VALUES (2, 3, 'Led Zeppelin IV', '1971-11-08', 'Atlantic Records');
INSERT INTO Cases (NumCDs, BoxNum, Title, ReleaseDate, RecordLabel) VALUES (1, 4, 'Recovery', '2010-06-18', 'Interscope Records');
INSERT INTO Cases (NumCDs, BoxNum, Title, ReleaseDate, RecordLabel) VALUES (2, 5, 'Kind of Blue', '1959-08-17', 'Columbia Records');
SELECT * FROM Cases;

-- Creating table for the relationship ArtistInfluencedbyArtist -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
CREATE TABLE ArtistInfluencedbyArtist (Influencer varchar(30), Influencee varchar(30),
									   FOREIGN KEY (Influencer) REFERENCES Artist(ArtistName) ON DELETE CASCADE ON UPDATE CASCADE,
									   FOREIGN KEY (Influencee) REFERENCES Artist(ArtistName) ON DELETE CASCADE ON UPDATE CASCADE);
INSERT INTO ArtistInfluencedbyArtist (Influencer, Influencee) VALUES ('Led Zeppelin', 'Pink Floyd');
INSERT INTO ArtistInfluencedbyArtist (Influencer, Influencee) VALUES ('Britney Spears', 'Kesha');
INSERT INTO ArtistInfluencedbyArtist (Influencer, Influencee) VALUES ('Maroon 5', 'Calvin Harris');
INSERT INTO ArtistInfluencedbyArtist (Influencer, Influencee) VALUES ('Eminem', 'French Montana');
INSERT INTO ArtistInfluencedbyArtist (Influencer, Influencee) VALUES ('Charlie Puth', 'Shawn Mendes');
SELECT * FROM ArtistInfluencedbyArtist;

--  Creating table for the relationship ArtistPlaysInstrument -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
CREATE TABLE ArtistPlaysInstrument (ArtistName varchar(30), InstrumentName varchar(15), PRIMARY KEY(ArtistName, InstrumentName),
									FOREIGN KEY (ArtistName) REFERENCES Artist(ArtistName) ON DELETE CASCADE ON UPDATE CASCADE,
                                    FOREIGN KEY (InstrumentName) REFERENCES Instrument(InstrumentName) ON DELETE CASCADE ON UPDATE CASCADE);
INSERT INTO ArtistPlaysInstrument (ArtistName, InstrumentName) VALUES ('Shawn Mendes', 'Guitar');
INSERT INTO ArtistPlaysInstrument (ArtistName, InstrumentName) VALUES ('Britney Spears', 'Voice');
INSERT INTO ArtistPlaysInstrument (ArtistName, InstrumentName) VALUES ('Kesha', 'Piano');
INSERT INTO ArtistPlaysInstrument (ArtistName, InstrumentName) VALUES ('Eminem', 'Drums');
INSERT INTO ArtistPlaysInstrument (ArtistName, InstrumentName) VALUES ('Charlie Puth', 'Piano');
INSERT INTO ArtistPlaysInstrument (ArtistName, InstrumentName) VALUES ('Miles Davis', 'Trumpet');
SELECT * FROM ArtistPlaysInstrument;

-- Creating table for the relationship SongSungbyArtist -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
CREATE TABLE SongSungbyArtist (SongName varchar(100), Composer varchar(50), ArtistName varchar(30), PRIMARY KEY (SongName, Composer, ArtistName),
							   FOREIGN KEY (SongName, Composer) REFERENCES Song(SongName, Composer) ON DELETE CASCADE ON UPDATE CASCADE,
                               FOREIGN KEY (ArtistName) REFERENCES Artist(ArtistName) ON DELETE CASCADE ON UPDATE CASCADE);
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Fate', 'Beethoven', 'Beethoven');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Ruins of Athens', 'Beethoven', 'Beethoven');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Moonlight', 'Beethoven', 'Beethoven');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Fur Elise', 'Beethoven', 'Beethoven');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Ode to Joy', 'Beethoven', 'Beethoven');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Eroica', 'Beethoven', 'Beethoven');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Choral Fantasy', 'Beethoven', 'Beethoven');

INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Speak to Me', 'Nick Mason', 'Pink Floyd');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Breathe', 'Roger Waters', 'Pink Floyd');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('On the Run', 'Roger Waters', 'Pink Floyd');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Time', 'Nick Mason', 'Pink Floyd');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('The Great Gig in the Sky', 'Richard Wright', 'Pink Floyd');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Money', 'Roger Waters', 'Pink Floyd');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Us and Them', 'Roger Waters', 'Pink Floyd');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Any Color You Like', 'David Gilmour', 'Pink Floyd');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Brain Damage', 'Roger Waters', 'Pink Floyd');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Eclipse', 'Roger Waters', 'Pink Floyd');

INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Black Dog', 'Jimmy Page', 'Led Zeppelin');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Rock and Roll', 'Jimmy Page', 'Led Zeppelin');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('The Battle of Evermore', 'Jimmy Page', 'Led Zeppelin');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Stairway to Heaven', 'Jimmy Page', 'Led Zeppelin');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Misty Mountain Hop', 'Jimmy Page', 'Led Zeppelin');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Four Sticks', 'Jimmy Page', 'Led Zeppelin');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Going to California', 'Jimmy Page', 'Led Zeppelin');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('When the Levee Breaks', 'Jimmy Page', 'Led Zeppelin');

INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('...Baby One More Time', 'Max Martin', 'Britney Spears');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('You Drive Me Crazy', 'Jorgen Elofsson', 'Britney Spears');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Sometimes', 'Jorgen Elofsson', 'Britney Spears');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Soda Pop', 'Mikey Bassie', 'Britney Spears');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Born to Make You Happy', 'Kristian Lundin', 'Britney Spears');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('From the Bottom of My Broken Heart', 'Eric Foster White', 'Britney Spears');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('I Will Be There', 'Max Martin', 'Britney Spears');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('I Will Still Love You', 'Eric Foster White', 'Britney Spears');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Thinkin About You', 'Mikey Bassie', 'Britney Spears');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('E-Mail My Heart', 'Eric Foster White', 'Britney Spears');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('The Beat Goes On', 'Sonny Bono', 'Britney Spears');

INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Attention', 'Charlie Puth', 'Charlie Puth');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Despacito', 'Luis Rodriguez', 'Luis Fonsi');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Theres Nothing Holdin Me Back', 'Shawn Mendes', 'Shawn Mendes');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('What About Us', 'Pink', 'Pink');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Strip That Down', 'Liam Payne', 'Liam Payne');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Feels', 'Adam Wiles', 'Calvin Harris');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('What Lovers Do', 'Adam Levine', 'Maroon 5');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Unforgettable', 'Karim Kharbouch', 'French Montana');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Redbone', 'Donald Glover', 'Childish Gambino');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Praying', 'Kesha Sebert', 'Kesha');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Make Me', 'Britney Spears', 'Britney Spears');

INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('So What', 'Miles Davis', 'Miles Davis');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Freddie Freeloader', 'Miles Davis', 'Miles Davis');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Blue in Green', 'Miles Davis', 'Miles Davis');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('All Blues', 'Miles Davis', 'Miles Davis');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Flamenco Sketches', 'Miles Davis', 'Miles Davis');

INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Cold Wind Blows', 'Marshall Mathers', 'Eminem');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Talkin 2 Myself', 'Marshall Mathers', 'Eminem');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('On Fire', 'Marshall Mathers', 'Eminem');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Wont Back Down', 'Marshall Mathers', 'Eminem');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('W.T.P.', 'Marshall Mathers', 'Eminem');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Going Through Changes', 'Marshall Mathers', 'Eminem');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Not Afraid', 'Marshall Mathers', 'Eminem');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Seduction', 'Marshall Mathers', 'Eminem');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('No Love', 'Marshall Mathers', 'Eminem');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Space Bound', 'Marshall Mathers', 'Eminem');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Cinderella Man', 'Marshall Mathers', 'Eminem');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('25 to Life', 'Marshall Mathers', 'Eminem');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('So Bad', 'Marshall Mathers', 'Eminem');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Almost Famous', 'Marshall Mathers', 'Eminem');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Love the Way You Lie', 'Marshall Mathers', 'Eminem');
INSERT INTO SongSungbyArtist (SongName, Composer, ArtistName) VALUES ('Youre Never Over', 'Marshall Mathers', 'Eminem');

SELECT * FROM SongSungbyArtist;

-- Creating table for Relationship CDContainsSong -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
CREATE TABLE CDContainsSong (SongName varchar(100), Composer varchar(50), Title varchar(100), ReleaseDate DATE, RecordLabel varchar(50), 
							 PRIMARY KEY (SongName, Composer, Title, ReleaseDate, RecordLabel),
                             FOREIGN KEY (SongName, Composer) REFERENCES Song(SongName, Composer) ON DELETE CASCADE ON UPDATE CASCADE,
                             FOREIGN KEY (Title, ReleaseDate, RecordLabel) REFERENCES CD(Title, ReleaseDate, RecordLabel) ON DELETE CASCADE ON UPDATE CASCADE);
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Fate', 'Beethoven', 'Beethoven Greatest Hits', '1991-09-06', 'RCA');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Ruins of Athens', 'Beethoven', 'Beethoven Greatest Hits', '1991-09-06', 'RCA');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Moonlight', 'Beethoven', 'Beethoven Greatest Hits', '1991-09-06', 'RCA');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Fur Elise', 'Beethoven', 'Beethoven Greatest Hits', '1991-09-06', 'RCA');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Ode to Joy', 'Beethoven', 'Beethoven Greatest Hits', '1991-09-06', 'RCA');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Eroica', 'Beethoven', 'Beethoven Greatest Hits', '1991-09-06', 'RCA');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Choral Fantasy', 'Beethoven', 'Beethoven Greatest Hits', '1991-09-06', 'RCA');

INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Speak to Me', 'Nick Mason', 'Dark Side of the Moon', '1973-03-01', 'Harvest Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Breathe', 'Roger Waters', 'Dark Side of the Moon', '1973-03-01', 'Harvest Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('On the Run', 'Roger Waters', 'Dark Side of the Moon', '1973-03-01', 'Harvest Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Time', 'Nick Mason', 'Dark Side of the Moon', '1973-03-01', 'Harvest Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('The Great Gig in the Sky', 'Richard Wright', 'Dark Side of the Moon', '1973-03-01', 'Harvest Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Money', 'Roger Waters', 'Dark Side of the Moon', '1973-03-01', 'Harvest Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Us and Them', 'Roger Waters', 'Dark Side of the Moon', '1973-03-01', 'Harvest Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Any Color You Like', 'David Gilmour', 'Dark Side of the Moon', '1973-03-01', 'Harvest Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Brain Damage', 'Roger Waters', 'Dark Side of the Moon', '1973-03-01', 'Harvest Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Eclipse', 'Roger Waters', 'Dark Side of the Moon', '1973-03-01', 'Harvest Records');

INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Black Dog', 'Jimmy Page', 'Led Zeppelin IV', '1971-11-08', 'Atlantic Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Rock and Roll', 'Jimmy Page', 'Led Zeppelin IV', '1971-11-08', 'Atlantic Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('The Battle of Evermore', 'Jimmy Page', 'Led Zeppelin IV', '1971-11-08', 'Atlantic Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Stairway to Heaven', 'Jimmy Page', 'Led Zeppelin IV', '1971-11-08', 'Atlantic Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Misty Mountain Hop', 'Jimmy Page', 'Led Zeppelin IV', '1971-11-08', 'Atlantic Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Four Sticks', 'Jimmy Page', 'Led Zeppelin IV', '1971-11-08', 'Atlantic Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Going to California', 'Jimmy Page', 'Led Zeppelin IV', '1971-11-08', 'Atlantic Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('When the Levee Breaks', 'Jimmy Page', 'Led Zeppelin IV', '1971-11-08', 'Atlantic Records');

INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('...Baby One More Time', 'Max Martin', '...Baby One More Time', '1999-01-12', 'Jive Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('You Drive Me Crazy', 'Jorgen Elofsson', '...Baby One More Time', '1999-01-12', 'Jive Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Sometimes', 'Jorgen Elofsson', '...Baby One More Time', '1999-01-12', 'Jive Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Soda Pop', 'Mikey Bassie', '...Baby One More Time', '1999-01-12', 'Jive Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Born to Make You Happy', 'Kristian Lundin', '...Baby One More Time', '1999-01-12', 'Jive Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('From the Bottom of My Broken Heart', 'Eric Foster White', '...Baby One More Time', '1999-01-12', 'Jive Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('I Will Be There', 'Max Martin', '...Baby One More Time', '1999-01-12', 'Jive Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('I Will Still Love You', 'Eric Foster White', '...Baby One More Time', '1999-01-12', 'Jive Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Thinkin About You', 'Mikey Bassie', '...Baby One More Time', '1999-01-12', 'Jive Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('E-Mail My Heart', 'Eric Foster White', '...Baby One More Time', '1999-01-12', 'Jive Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('The Beat Goes On', 'Sonny Bono', '...Baby One More Time', '1999-01-12', 'Jive Records');

INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Attention', 'Charlie Puth', 'Now Thats What I Call Music 64', '2017-11-03', 'Sony Music');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Despacito', 'Luis Rodriguez', 'Now Thats What I Call Music 64', '2017-11-03', 'Sony Music');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Theres Nothing Holdin Me Back', 'Shawn Mendes', 'Now Thats What I Call Music 64', '2017-11-03', 'Sony Music');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('What About Us', 'Pink', 'Now Thats What I Call Music 64', '2017-11-03', 'Sony Music');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Strip That Down', 'Liam Payne', 'Now Thats What I Call Music 64', '2017-11-03', 'Sony Music');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Feels', 'Adam Wiles', 'Now Thats What I Call Music 64', '2017-11-03', 'Sony Music');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('What Lovers Do', 'Adam Levine', 'Now Thats What I Call Music 64', '2017-11-03', 'Sony Music');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Unforgettable', 'Karim Kharbouch', 'Now Thats What I Call Music 64', '2017-11-03', 'Sony Music');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Redbone', 'Donald Glover', 'Now Thats What I Call Music 64', '2017-11-03', 'Sony Music');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Praying', 'Kesha Sebert', 'Now Thats What I Call Music 64', '2017-11-03', 'Sony Music');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Make Me', 'Britney Spears', 'Now Thats What I Call Music 64', '2017-11-03', 'Sony Music');

INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('So What', 'Miles Davis', 'Kind of Blue', '1959-08-17', 'Columbia Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Freddie Freeloader', 'Miles Davis', 'Kind of Blue', '1959-08-17', 'Columbia Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Blue in Green', 'Miles Davis', 'Kind of Blue', '1959-08-17', 'Columbia Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('All Blues', 'Miles Davis', 'Kind of Blue', '1959-08-17', 'Columbia Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Flamenco Sketches', 'Miles Davis', 'Kind of Blue', '1959-08-17', 'Columbia Records');

INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Cold Wind Blows', 'Marshall Mathers', 'Recovery', '2010-06-18', 'Interscope Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Talkin 2 Myself', 'Marshall Mathers', 'Recovery', '2010-06-18', 'Interscope Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('On Fire', 'Marshall Mathers', 'Recovery', '2010-06-18', 'Interscope Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Wont Back Down', 'Marshall Mathers', 'Recovery', '2010-06-18', 'Interscope Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('W.T.P.', 'Marshall Mathers', 'Recovery', '2010-06-18', 'Interscope Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Going Through Changes', 'Marshall Mathers', 'Recovery', '2010-06-18', 'Interscope Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Not Afraid', 'Marshall Mathers', 'Recovery', '2010-06-18', 'Interscope Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Seduction', 'Marshall Mathers', 'Recovery', '2010-06-18', 'Interscope Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('No Love', 'Marshall Mathers', 'Recovery', '2010-06-18', 'Interscope Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Space Bound', 'Marshall Mathers', 'Recovery', '2010-06-18', 'Interscope Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Cinderella Man', 'Marshall Mathers', 'Recovery', '2010-06-18', 'Interscope Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('25 to Life', 'Marshall Mathers', 'Recovery', '2010-06-18', 'Interscope Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('So Bad', 'Marshall Mathers', 'Recovery', '2010-06-18', 'Interscope Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Almost Famous', 'Marshall Mathers', 'Recovery', '2010-06-18', 'Interscope Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Love the Way You Lie', 'Marshall Mathers', 'Recovery', '2010-06-18', 'Interscope Records');
INSERT INTO CDContainsSong (SongName, Composer, Title, ReleaseDate, RecordLabel) VALUES ('Youre Never Over', 'Marshall Mathers', 'Recovery', '2010-06-18', 'Interscope Records');
SELECT * FROM CDContainsSong;

-- Creating table for artist belongs to genre -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
CREATE TABLE ArtistBelongstoGenre (ArtistName varchar(30), GenreName varchar(15), PRIMARY KEY(ArtistName, GenreName),
								   FOREIGN KEY (ArtistName) REFERENCES Artist(ArtistName) ON DELETE CASCADE ON UPDATE CASCADE,
                                   FOREIGN KEY (GenreName) REFERENCES Genre(GenreName) ON DELETE CASCADE ON UPDATE CASCADE);
INSERT INTO ArtistBelongstoGenre (ArtistName, GenreName) VALUES ('Pink Floyd', 'Rock');
INSERT INTO ArtistBelongstoGenre (ArtistName, GenreName) VALUES ('Led Zeppelin', 'Rock');
INSERT INTO ArtistBelongstoGenre (ArtistName, GenreName) VALUES ('Beethoven', 'Classical');
INSERT INTO ArtistBelongstoGenre (ArtistName, GenreName) VALUES ('Britney Spears', 'Pop');
INSERT INTO ArtistBelongstoGenre (ArtistName, GenreName) VALUES ('Eminem', 'Rap');
INSERT INTO ArtistBelongstoGenre (ArtistName, GenreName) VALUES ('Charlie Puth', 'Pop');
INSERT INTO ArtistBelongstoGenre (ArtistName, GenreName) VALUES ('Luis Fonsi', 'Pop');
INSERT INTO ArtistBelongstoGenre (ArtistName, GenreName) VALUES ('Shawn Mendes', 'Pop');
INSERT INTO ArtistBelongstoGenre (ArtistName, GenreName) VALUES ('Pink', 'Pop');
INSERT INTO ArtistBelongstoGenre (ArtistName, GenreName) VALUES ('Liam Payne', 'Pop');
INSERT INTO ArtistBelongstoGenre (ArtistName, GenreName) VALUES ('Calvin Harris', 'Pop');
INSERT INTO ArtistBelongstoGenre (ArtistName, GenreName) VALUES ('Maroon 5', 'Pop');
INSERT INTO ArtistBelongstoGenre (ArtistName, GenreName) VALUES ('French Montana', 'Rap');
INSERT INTO ArtistBelongstoGenre (ArtistName, GenreName) VALUES ('Childish Gambino', 'Rap');
INSERT INTO ArtistBelongstoGenre (ArtistName, GenreName) VALUES ('Kesha', 'Pop');
INSERT INTO ArtistBelongstoGenre (ArtistName, GenreName) VALUES ('Miles Davis', 'Jazz');
SELECT * FROM ArtistBelongstoGenre;

-- Creating table for the relationship ListenerListenstoCD -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
CREATE TABLE ListenerListenstoCD (ListenerName varchar(10), Address varchar(30), Title varchar(100), ReleaseDate DATE, RecordLabel varchar(50), 
								  PRIMARY KEY(ListenerName, Address, Title, ReleaseDate, RecordLabel),
                                  FOREIGN KEY (ListenerName, Address) REFERENCES Listener(ListenerName, Address) ON DELETE CASCADE ON UPDATE CASCADE,
                                  FOREIGN KEY (Title, ReleaseDate, RecordLabel) REFERENCES CD(Title, ReleaseDate, RecordLabel) ON DELETE CASCADE ON UPDATE CASCADE);
INSERT INTO ListenerListenstoCD (ListenerName, Address, Title, ReleaseDate, RecordLabel) VALUES ('Joe', '123 Maple Drive', 'Recovery', '2010-06-18', 'Interscope Records');
INSERT INTO ListenerListenstoCD (ListenerName, Address, Title, ReleaseDate, RecordLabel) VALUES ('Katie', '789 Beech Street', 'Dark Side of the Moon', '1973-03-01', 'Harvest Records');
INSERT INTO ListenerListenstoCD (ListenerName, Address, Title, ReleaseDate, RecordLabel) VALUES ('Katie', '789 Beech Street', 'Led Zeppelin IV', '1971-11-08', 'Atlantic Records');
INSERT INTO ListenerListenstoCD (ListenerName, Address, Title, ReleaseDate, RecordLabel) VALUES ('Bob', '456 Oak Lane', 'Kind of Blue', '1959-08-17', 'Columbia Records');
INSERT INTO ListenerListenstoCD (ListenerName, Address, Title, ReleaseDate, RecordLabel) VALUES ('Crystal', '246 Pine Boulevard', '...Baby One More Time', '1999-01-12', 'Jive Records');
INSERT INTO ListenerListenstoCD (ListenerName, Address, Title, ReleaseDate, RecordLabel) VALUES ('Elliot', '357 Walnut Lane', 'Beethoven Greatest Hits', '1991-09-06', 'RCA');
INSERT INTO ListenerListenstoCD (ListenerName, Address, Title, ReleaseDate, RecordLabel) VALUES ('Joe', '123 Maple Drive', 'Now Thats What I Call Music 64', '2017-11-03', 'Sony Music');
SELECT * FROM ListenerListenstoCD;

-- Creating table for relationship ListenerPrefersGenre -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
CREATE TABLE ListenerPrefersGenre (ListenerName varchar(10), Address varchar(30), GenreName varchar(15), _Time varchar(15), Place varchar(15), 
								   PRIMARY KEY (ListenerName, Address, GenreName, _Time, Place),
                                   FOREIGN KEY (ListenerName, Address) REFERENCES Listener(ListenerName, Address) ON DELETE CASCADE ON UPDATE CASCADE,
                                   FOREIGN KEY (GenreName) REFERENCES Genre(GenreName) ON DELETE CASCADE ON UPDATE CASCADE);
INSERT INTO ListenerPrefersGenre (ListenerName, Address, GenreName, _Time, Place)  VALUES ('Joe', '123 Maple Drive', 'Classical', 'Night', 'Home');
INSERT INTO ListenerPrefersGenre (ListenerName, Address, GenreName, _Time, Place)  VALUES ('Katie', '789 Beech Street', 'Classical', 'Afternoon', 'Work');
INSERT INTO ListenerPrefersGenre (ListenerName, Address, GenreName, _Time, Place)  VALUES ('Bob', '456 Oak Lane', 'Rock', 'Morning', 'School');
INSERT INTO ListenerPrefersGenre (ListenerName, Address, GenreName, _Time, Place)  VALUES ('Crystal', '246 Pine Boulevard', 'Pop', 'Afternoon', 'School');
INSERT INTO ListenerPrefersGenre (ListenerName, Address, GenreName, _Time, Place)  VALUES ('Crystal', '246 Pine Boulevard', 'Jazz', 'Night', 'Home');
INSERT INTO ListenerPrefersGenre (ListenerName, Address, GenreName, _Time, Place)  VALUES ('Elliot', '357 Walnut Lane', 'Rap', 'Morning', 'Gym');
SELECT * FROM ListenerPrefersGenre;

-- Creating table for the relationship ListenerRatesSong -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
CREATE TABLE ListenerRatesSong (SongName varchar(50), ListenerName varchar(10), Address varchar(30), Rating real, 
							    PRIMARY KEY (SongName, ListenerName, Address),
                                FOREIGN KEY (SongName) REFERENCES Song(SongName) ON DELETE CASCADE ON UPDATE CASCADE,
                                FOREIGN KEY (ListenerName, Address) REFERENCES Listener(ListenerName, Address) ON DELETE CASCADE ON UPDATE CASCADE);
INSERT INTO ListenerRatesSong (SongName, ListenerName, Address, Rating) VALUES ('Moonlight', 'Joe', '123 Maple Drive', 5.0);
INSERT INTO ListenerRatesSong (SongName, ListenerName, Address, Rating) VALUES ('Breathe', 'Crystal', '246 Pine Boulevard', 2.2);
INSERT INTO ListenerRatesSong (SongName, ListenerName, Address, Rating) VALUES ('Stairway to Heaven', 'Katie', '789 Beech Street', 4.8);
INSERT INTO ListenerRatesSong (SongName, ListenerName, Address, Rating) VALUES ('Eclipse', 'Elliot', '357 Walnut Lane', 3.3);
INSERT INTO ListenerRatesSong (SongName, ListenerName, Address, Rating) VALUES ('Four Sticks', 'Bob', '456 Oak Lane', 4.6);
INSERT INTO ListenerRatesSong (SongName, ListenerName, Address, Rating) VALUES ('Sometimes', 'Crystal', '246 Pine Boulevard', 3.9);
INSERT INTO ListenerRatesSong (SongName, ListenerName, Address, Rating) VALUES ('The Beat Goes On', 'Bob', '456 Oak Lane', 1.2);
INSERT INTO ListenerRatesSong (SongName, ListenerName, Address, Rating) VALUES ('Attention', 'Katie', '789 Beech Street', 2.9);
INSERT INTO ListenerRatesSong (SongName, ListenerName, Address, Rating) VALUES ('Feels', 'Joe', '123 Maple Drive', 3.5);
INSERT INTO ListenerRatesSong (SongName, ListenerName, Address, Rating) VALUES ('So What', 'Crystal', '246 Pine Boulevard', 4.2);
INSERT INTO ListenerRatesSong (SongName, ListenerName, Address, Rating) VALUES ('Not Afraid', 'Elliot', '357 Walnut Lane', 4.9);
INSERT INTO ListenerRatesSong (SongName, ListenerName, Address, Rating) VALUES ('Moonlight', 'Elliot', '357 Walnut Lane', 4.9);
SELECT * FROM ListenerRatesSong;

-- Creating table for relationship SongIsGenre -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
CREATE TABLE SongIsGenre (SongName varchar(100), Composer varchar(50), GenreName varchar(20), 
						  PRIMARY KEY (SongName, Composer, GenreName),
                          FOREIGN KEY (SongName, Composer) REFERENCES Song(SongName, Composer) ON DELETE CASCADE ON UPDATE CASCADE,
                          FOREIGN KEY (GenreName) REFERENCES Genre(GenreName) ON DELETE CASCADE ON UPDATE CASCADE);
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Fate', 'Beethoven', 'Classical');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Ruins of Athens', 'Beethoven', 'Classical');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Moonlight', 'Beethoven', 'Classical');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Fur Elise', 'Beethoven', 'Classical');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Ode to Joy', 'Beethoven', 'Classical');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Eroica', 'Beethoven', 'Classical');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Choral Fantasy', 'Beethoven', 'Classical');

INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Speak to Me', 'Nick Mason', 'Rock');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Breathe', 'Roger Waters', 'Rock');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('On the Run', 'Roger Waters', 'Rock');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Time', 'Nick Mason', 'Rock');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('The Great Gig in the Sky', 'Richard Wright', 'Rock');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Money', 'Roger Waters', 'Rock');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Us and Them', 'Roger Waters', 'Rock');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Any Color You Like', 'David Gilmour', 'Rock');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Brain Damage', 'Roger Waters', 'Rock');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Eclipse', 'Roger Waters', 'Rock');

INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Black Dog', 'Jimmy Page', 'Rock');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Rock and Roll', 'Jimmy Page', 'Rock');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('The Battle of Evermore', 'Jimmy Page', 'Rock');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Stairway to Heaven', 'Jimmy Page', 'Rock');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Misty Mountain Hop', 'Jimmy Page', 'Rock');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Four Sticks', 'Jimmy Page', 'Rock');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Going to California', 'Jimmy Page', 'Rock');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('When the Levee Breaks', 'Jimmy Page', 'Rock');

INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('...Baby One More Time', 'Max Martin', 'Pop');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('You Drive Me Crazy', 'Jorgen Elofsson', 'Pop');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Sometimes', 'Jorgen Elofsson', 'Pop');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Soda Pop', 'Mikey Bassie', 'Pop');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Born to Make You Happy', 'Kristian Lundin', 'Pop');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('From the Bottom of My Broken Heart', 'Eric Foster White', 'Pop');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('I Will Be There', 'Max Martin', 'Pop');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('I Will Still Love You', 'Eric Foster White', 'Pop');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Thinkin About You', 'Mikey Bassie', 'Pop');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('E-Mail My Heart', 'Eric Foster White', 'Pop');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('The Beat Goes On', 'Sonny Bono', 'Pop');

INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Attention', 'Charlie Puth', 'Pop');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Despacito', 'Luis Rodriguez', 'Pop');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Theres Nothing Holdin Me Back', 'Shawn Mendes', 'Pop');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('What About Us', 'Pink', 'Pop');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Strip That Down', 'Liam Payne', 'Pop');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Feels', 'Adam Wiles', 'Pop');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('What Lovers Do', 'Adam Levine', 'Pop');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Unforgettable', 'Karim Kharbouch', 'Rap');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Redbone', 'Donald Glover', 'Rap');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Praying', 'Kesha Sebert', 'Pop');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Make Me', 'Britney Spears', 'Pop');


INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('So What', 'Miles Davis', 'Jazz');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Freddie Freeloader', 'Miles Davis', 'Jazz');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Blue in Green', 'Miles Davis', 'Jazz');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('All Blues', 'Miles Davis', 'Jazz');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Flamenco Sketches', 'Miles Davis', 'Jazz');

INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Cold Wind Blows', 'Marshall Mathers', 'Rap');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Talkin 2 Myself', 'Marshall Mathers', 'Rap');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('On Fire', 'Marshall Mathers', 'Rap');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Wont Back Down', 'Marshall Mathers', 'Rap');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('W.T.P.', 'Marshall Mathers', 'Rap');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Going Through Changes', 'Marshall Mathers', 'Rap');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Not Afraid', 'Marshall Mathers', 'Rap');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Seduction', 'Marshall Mathers', 'Rap');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('No Love', 'Marshall Mathers', 'Rap');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Space Bound', 'Marshall Mathers', 'Rap');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Cinderella Man', 'Marshall Mathers', 'Rap');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('25 to Life', 'Marshall Mathers', 'Rap');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('So Bad', 'Marshall Mathers', 'Rap');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Almost Famous', 'Marshall Mathers', 'Rap');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Love the Way You Lie', 'Marshall Mathers', 'Rap');
INSERT INTO SongIsGenre (SongName, Composer, GenreName) VALUES ('Youre Never Over', 'Marshall Mathers', 'Rap');
SELECT * FROM SongIsGenre;


-- Queries

-- 1. Show All Cds
SELECT Title FROM CD;

-- 2. Show All CDs that are in Box 1
SELECT Title, ReleaseDate, RecordLabel FROM Cases WHERE BoxNum = 1;

-- 3. Show All CDs who are in a red box
SELECT Title, ReleaseDate, RecordLabel FROM Cases NATURAL JOIN Box WHERE Color = 'Red';

-- 4. Which song has the maximum length?
CREATE TEMPORARY TABLE TableA (SELECT MAX(Length) AS Length FROM Song);
SELECT SongName, Length FROM Song NATURAL JOIN TableA;

-- 5. Which song has the highest average rating?
CREATE TEMPORARY TABLE TableB(SELECT SongName, AVG(Rating) AS Rating FROM ListenerRatesSong GROUP BY SongName);
CREATE TEMPORARY TABLE TableC (SELECT MAX(Rating) AS Rating FROM TableB);
SELECT SongName, Rating FROM TableB NATURAL JOIN TableC;

-- 6. Which CD has the most songs contibuted by different artists?
CREATE TEMPORARY TABLE TableD (SELECT * FROM SongSungbyArtist NATURAL JOIN CDContainsSong);
CREATE TEMPORARY TABLE TableE (SELECT Title, ReleaseDate, RecordLabel, COUNT(DISTINCT(ArtistName)) AS NumArtists FROM TableD GROUP BY Title, ReleaseDate, RecordLabel);
CREATE TEMPORARY TABLE TableF (SELECT Title, ReleaseDate, RecordLabel, MAX(NumArtists) AS MaxArtists FROM TableE GROUP BY Title, ReleaseDate, RecordLabel); 
CREATE TEMPORARY TABLE TableG (SELECT MAX(MaxArtists) AS MaxArtists FROM TableF);
SELECT * FROM TableF NATURAL JOIN TableG;

-- 7. Show for every artist the influenced musician
SELECT Influencer AS ArtistName, Influencee AS InfluencedMusician FROM ArtistInfluencedbyArtist;

-- 8. Show for every artist the number of cds they contributed to
CREATE TEMPORARY TABLE TableH (SELECT Title, ReleaseDate, RecordLabel, ArtistName FROM SongSungbyArtist NATURAL JOIN CDContainsSong);
SELECT ArtistName, COUNT(DISTINCT(Title)) AS NumCDsContributed FROM TableH GROUP BY ArtistName;

-- 9. Show for all listeners the preferred music when they are at work
SELECT * FROM ListenerPrefersGenre WHERE Place='Work';

-- 10. How many artists belong to the different genres 
SELECT GenreName, COUNT(ArtistName) AS NumArtists FROM ArtistBelongstoGenre GROUP BY GenreName;


DROP TABLE TableA;
DROP TABLE TableB;
DROP TABLE TableC;
DROP TABLE TableD;
DROP TABLE TableE;
DROP TABLE TableF;
DROP TABLE TableG;
DROP TABLE TableH;

DROP TABLE Cases;

DROP TABLE ArtistInfluencedbyArtist;
DROP TABLE ArtistPlaysInstrument;
DROP TABLE SongSungbyArtist;
DROP TABLE CDContainsSong;
DROP TABLE ArtistBelongstoGenre;
DROP TABLE ListenerListenstoCD;
DROP TABLE ListenerPrefersGenre;
DROP TABLE ListenerRatesSong;
DROP TABLE SongIsGenre;

DROP TABLE Genre;
DROP TABLE Listener;
DROP TABLE Box;
DROP TABLE CD;
DROP TABLE Song;
DROP TABLE Artist;
DROP TABLE Instrument;


