from django.shortcuts import render
from django.http import HttpResponse
from django.shortcuts import render
from .models import INT

def homePage(request):

	un=''
	potV=0
	print(dict(request.GET))

	if 'username' in dict(request.GET).keys():
		if dict(request.GET)['username'][0] == 'nodemcu': un= 'nodemcu' #username --> nodemcu
	if un == 'nodemcu':
		if 'pot' in dict(request.GET).keys():
			potV= int(dict(request.GET)['pot'][0])
			if len(INT.objects.all()) == 0:
				x= INT(integer=potV, index=0)
				x.save()
			else:
				y=INT.objects.filter(index=0)
				y.delete()
				x= INT(integer=potV, index=0)
				x.save()
	else:
		return render(request, 'home.html', {'pot': INT.objects.get(index=0)})

	return HttpResponse('bonjour')

	'''print(potV)
	return render(request, 'home.html', {'pot': potV})'''


