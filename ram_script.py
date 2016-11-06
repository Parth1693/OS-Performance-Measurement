from subprocess import call

arr_size = 256

for x in range(20):
	args = ['./ram_latency',str(arr_size),'1']
	call(args)
	arr_size = arr_size * 2

#for x in range(10):
#	stride = 256
#	for y in range(10):
#		args = ['./ram_latency',str(arr_size),str(stride)]
#		call(args)
#		stride = stride * 4
#	arr_size = arr_size * 4
