from django.db import models

class INT(models.Model):
	integer= models.IntegerField(default=None, null=True)
	index= models.IntegerField(default=None, null=True)

	def __str__(self):
		return str(self.integer)
