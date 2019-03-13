# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.contrib import admin
from .models import Table_GPS, Horizontal, Vertical, Conductivity, Compass
# Register your models here.
admin.site.register(Table_GPS)
admin.site.register(Horizontal)
admin.site.register(Vertical)
admin.site.register(Conductivity)
admin.site.register(Compass)
