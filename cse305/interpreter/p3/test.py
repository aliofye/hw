class Closure():
	def __init__(self):
		self.loathing = list()
		self.arg = dict()

closure = Closure()
boolean = True if type(closure) is type(Closure()) else False
print(boolean)