from django.shortcuts import render
from django.http import HttpResponse
from django.shortcuts import render

def homePage(request):

	un=''
	potV=0

	if 'username' in dict(request.GET).keys():
		if dict(request.GET)['username'] == 'nodemcu': un= 'nodemcu' #username --> nodemcu
	if un == 'nodemcu':
		if 'pot' in dict(request.GET).keys(): potV= dict(request.GET)['pot']
	print(potV)


