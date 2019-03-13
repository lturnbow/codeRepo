# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models
from django.utils import timezone

# Create your models here.
# Each class represents a table in the database and each variable is an attribute
class Table_GPS(models.Model):
	DayTime = models.DateTimeField(default=timezone.now, blank=True, primary_key=True) # DateTimeField holds the date and the time
	Version = models.IntegerField(default=0)
	E = models.IntegerField(default=0)
	Sequence = models.IntegerField(default=0)
	Latitude = models.DecimalField(max_digits=8, decimal_places=5)
	Longitude = models.DecimalField(max_digits=8, decimal_places=5)
	Altitude = models.IntegerField()
	
class Horizontal(models.Model):
	DayTime = models.DateTimeField(default=timezone.now, blank=True, primary_key=True)
	Horiz1_1 = models.IntegerField()
	Horiz1_2 = models.IntegerField()
	Horiz1_3 = models.IntegerField()
	Horiz1_4 = models.IntegerField()
	Horiz1_5 = models.IntegerField()
	Horiz1_6 = models.IntegerField()
	Horiz1_7 = models.IntegerField()
	Horiz1_8 = models.IntegerField()
	Horiz1_9 = models.IntegerField()
	Horiz1_10 = models.IntegerField()
	Horiz1_11 = models.IntegerField()
	Horiz1_12 = models.IntegerField()
	
	Horiz2_1 = models.IntegerField()
	Horiz2_2 = models.IntegerField()
	Horiz2_3 = models.IntegerField()
	Horiz2_4 = models.IntegerField()
	Horiz2_5 = models.IntegerField()
	Horiz2_6 = models.IntegerField()
	Horiz2_7 = models.IntegerField()
	Horiz2_8 = models.IntegerField()
	Horiz2_9 = models.IntegerField()
	Horiz2_10 = models.IntegerField()
	Horiz2_11 = models.IntegerField()
	Horiz2_12 = models.IntegerField()
	
	HorizD_1 = models.IntegerField()
	HorizD_2 = models.IntegerField()
	HorizD_3 = models.IntegerField()
	HorizD_4 = models.IntegerField()
	HorizD_5 = models.IntegerField()
	HorizD_6 = models.IntegerField()
	HorizD_7 = models.IntegerField()
	HorizD_8 = models.IntegerField()
	HorizD_9 = models.IntegerField()
	HorizD_10 = models.IntegerField()
	HorizD_11 = models.IntegerField()
	HorizD_12 = models.IntegerField()
	
class Vertical(models.Model):
	DayTime = models.DateTimeField(default=timezone.now, blank=True, primary_key=True)
	
	Vert1 = models.IntegerField()
	Vert2 = models.IntegerField()
	VertD = models.IntegerField()
	
class Conductivity(models.Model):
	DayTime = models.DateTimeField(default=timezone.now, blank=True, primary_key=True)
	cVert1_1 = models.IntegerField()
	cVert1_2 = models.IntegerField()
	cVert1_3 = models.IntegerField()
	cVert1_4 = models.IntegerField()
	cVert1_5 = models.IntegerField()
	cVert1_6 = models.IntegerField()
	cVert1_7 = models.IntegerField()
	cVert1_8 = models.IntegerField()
	cVert1_9 = models.IntegerField()
	cVert1_10 = models.IntegerField()
	cVert1_11 = models.IntegerField()
	cVert1_12 = models.IntegerField()
	cVert1_13 = models.IntegerField()
	cVert1_14 = models.IntegerField()
	cVert1_15 = models.IntegerField()
	
	cVert2_1 = models.IntegerField()
	cVert2_2 = models.IntegerField()
	cVert2_3 = models.IntegerField()
	cVert2_4 = models.IntegerField()
	cVert2_5 = models.IntegerField()
	cVert2_6 = models.IntegerField()
	cVert2_7 = models.IntegerField()
	cVert2_8 = models.IntegerField()
	cVert2_9 = models.IntegerField()
	cVert2_10 = models.IntegerField()
	cVert2_11 = models.IntegerField()
	cVert2_12 = models.IntegerField()
	cVert2_13 = models.IntegerField()
	cVert2_14 = models.IntegerField()
	cVert2_15 = models.IntegerField()
	
	TimeConstant = models.DecimalField(decimal_places=4, max_digits=8)
	
class Compass(models.Model):
	DayTime = models.DateTimeField(default=timezone.now, blank=True, primary_key=True)
	CompassX_1 = models.IntegerField()
	CompassX_2 = models.IntegerField()
	CompassX_3 = models.IntegerField()
	CompassX_4 = models.IntegerField()
	CompassX_5 = models.IntegerField()
	CompassX_6 = models.IntegerField()
	CompassX_7 = models.IntegerField()
	CompassX_8 = models.IntegerField()
	CompassX_9 = models.IntegerField()
	CompassX_10 = models.IntegerField()
	CompassX_11 = models.IntegerField()
	CompassX_12 = models.IntegerField()
	
	CompassY_1 = models.IntegerField()
	CompassY_2 = models.IntegerField()
	CompassY_3 = models.IntegerField()
	CompassY_4 = models.IntegerField()
	CompassY_5 = models.IntegerField()
	CompassY_6 = models.IntegerField()
	CompassY_7 = models.IntegerField()
	CompassY_8 = models.IntegerField()
	CompassY_9 = models.IntegerField()
	CompassY_10 = models.IntegerField()
	CompassY_11 = models.IntegerField()
	CompassY_12 = models.IntegerField()
	
	
