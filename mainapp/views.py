from django.shortcuts import render
from django.http import HttpResponse

def homePage(request):
	print(request.GET)
	return HttpResponse('Bonjour!')

