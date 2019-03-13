"""tutorial URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/1.11/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  url(r'^$', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  url(r'^$', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.conf.urls import url, include
    2. Add a URL to urlpatterns:  url(r'^blog/', include('blog.urls'))
"""
from django.conf.urls import url
from django.contrib import admin

from tutorialapp.views import tables, homepage, mapPlot, altitude, horizontal, vertical, compass, conductivity, _pdf, _csv

from wkhtmltopdf.views import PDFTemplateView
from django.conf import settings
from django.conf.urls.static import static
# These are the urls for each page that can be accessed
urlpatterns = [
	url(r'^$', homepage, name='homepage'),
	url(r'^pdf/$', _pdf, name='_pdf'),
	url(r'^csv/$', _csv, name='_csv'),
	url(r'^tables/$', tables, name='tables'),
	url(r'^mapPlot/$', mapPlot, name='mapPlot'),
	url(r'^altitude/$', altitude, name='altitude'),
	url(r'^horizontal/$', horizontal, name='horizontal'),
	url(r'^vertical/$', vertical, name='vertical'),
	url(r'^compass/$', compass, name='compass'),
	url(r'^conductivity/$', conductivity, name='conductivity'),
	url(r'^pdf/$', PDFTemplateView.as_view(template_name='tutorial/tables.html', filename='my_pdf.pdf'), name='pdf'),
] + static(settings.MEDIA_URL, document_root=settings.MEDIA_ROOT)
