import subprocess
import shlex
import xlwt
import math
import statistics

num_tests = 10
subprocess.call(['make','clean'])
subprocess.call(['make'])

values = {}
#RDTSC overhead
rdtsc_vals = []
for i in range(num_tests):
	args_rdtsc = ['./rdtsc_overhead']
	process = subprocess.Popen(args_rdtsc, stdout=subprocess.PIPE)
	while True:
		output = process.stdout.readline()
		if output == '' and process.poll() is not None:
			break
		if output:
			rdtsc_vals.append(output.strip())
values['rdtsc'] = rdtsc_vals

#Procedure call
proc_call_vals = []
for i in range(num_tests):
	args = ['./procedure_call','8']
	process = subprocess.Popen(args, stdout=subprocess.PIPE)
	while True:
		output = process.stdout.readline()
		if output == '' and process.poll() is not None:
			break
		if output:
			proc_call_vals.append(output.strip())
values['procedure call'] = proc_call_vals

#System call
sys_call_vals = []
for i in range(num_tests):
	args = ['./syscall']
	process = subprocess.Popen(args, stdout=subprocess.PIPE)
	while True:
		output = process.stdout.readline()
		if output == '' and process.poll() is not None:
			break
		if output:
			sys_call_vals.append(output.strip())
values['system call'] = sys_call_vals

#Process creation overhead
cr_proc_vals = []
for i in range(num_tests):
	args_create_process = ['./create_process']
	process = subprocess.Popen(args_create_process, stdout=subprocess.PIPE)
	while True:
		output = process.stdout.readline()
		if output == '' and process.poll() is not None:
			break
		if output:
			cr_proc_vals.append(output.strip())
values['process creation'] = cr_proc_vals

#Thread creation overhead
cr_thread_vals = []
for i in range(num_tests):
	args_create_thread = ['./create_thread']
	process = subprocess.Popen(args_create_thread, stdout=subprocess.PIPE)
	while True:
		output = process.stdout.readline()
		if output == '' and process.poll() is not None:
			break
		if output:
			cr_thread_vals.append(output.strip())
values['thread creation'] = cr_thread_vals

#CS Process
cs_proc_vals = []
for i in range(num_tests):
	args_cs_proc = ['./cswitch_process']
	process = subprocess.Popen(args_cs_proc, stdout=subprocess.PIPE)
	while True:
		output = process.stdout.readline()
		if output == '' and process.poll() is not None:
			break
		if output:
			cs_proc_vals.append(output.strip())
values['context switch process'] = cs_proc_vals

#CS Thread
cs_thread_vals = []
for i in range(num_tests):
	args_cs_thread = ['./cswitch_thread']
	process = subprocess.Popen(args_cs_thread, stdout=subprocess.PIPE)
	while True:
		output = process.stdout.readline()
		if output == '' and process.poll() is not None:
			break
		if output:
			cs_thread_vals.append(output.strip())
values['context switch thread'] = cs_thread_vals


#Page fault
pf_vals = []
for i in range(num_tests):
	args = ['./page_fault']
	process = subprocess.Popen(args, stdout=subprocess.PIPE)
	while True:
		output = process.stdout.readline()
		if output == '' and process.poll() is not None:
			break
		if output:
			pf_vals.append(output.strip())
values['page fault'] = pf_vals

#Put PART 1+Pagefault in worksheet
book = xlwt.Workbook(encoding="utf-8")

for key,value in values.iteritems():
	sheet1 = book.add_sheet(key)
	sheet1.write(1,1,key)
	i=2
	for entry in value:
		#print key,entry		
		sheet1.write(i,1,int(entry))
		i=i+1


#RAM Bandwidth Read
bw_range = 3
bw_arr_size = 1024*1024*512
bw_arr_size = bw_arr_size / 4
ram_bw_rd_vals = []
arr_size = bw_arr_size
for x in range(bw_range):
	each_arr_size_vals = []
	for i in range(num_tests):
		args = ['./ram_bw',str(arr_size),'0']
		process = subprocess.Popen(args, stdout=subprocess.PIPE)
		while True:
			output = process.stdout.readline()
			if output == '' and process.poll() is not None:
				break
			if output:
				each_arr_size_vals.append(int(output.strip()))
	arr_size = arr_size * 2
	value = statistics.mean(each_arr_size_vals)
	ram_bw_rd_vals.append(float(value))

#RAM Bandwidth Write
ram_bw_wr_vals = []
arr_size = bw_arr_size
for x in range(bw_range):
	each_arr_size_vals = []
	for i in range(num_tests):
		args = ['./ram_bw',str(arr_size),'1']
		process = subprocess.Popen(args, stdout=subprocess.PIPE)
		while True:
			output = process.stdout.readline()
			if output == '' and process.poll() is not None:
				break
			if output:
				each_arr_size_vals.append(int(output.strip()))
	arr_size = arr_size * 2
	value = statistics.mean(each_arr_size_vals)
	ram_bw_wr_vals.append(float(value))

sheet1 = book.add_sheet("RAM Bandwidth")
sheet1.write(1,2,"RAM Bandwidth Read")
sheet1.write(1,5,"RAM Bandwidth Write")
arr_size = bw_arr_size
for x in range(bw_range):
	sheet1.write(x+2,1,math.log(arr_size*4,2))
	sheet1.write(x+2,2,int(ram_bw_rd_vals[x]))
	sheet1.write(x+2,5,int(ram_bw_wr_vals[x]))
	arr_size = arr_size * 2


'''
#RAM Latency
latency_range = 16
array_size = 256
stride_size = 16
ram_latency_highlevel = []
for i in range(num_tests):	
	ram_latency_vals = []
	arr_size = array_size
	for x in range(latency_range):
		stride = stride_size
		for y in range(latency_range):
			if stride>=arr_size:
				break
			args = ['./ram_latency',str(arr_size),str(stride),'1',str(stride)]
			process = subprocess.Popen(args, stdout=subprocess.PIPE)
			while True:
				output = process.stdout.readline()
				if output == '' and process.poll() is not None:
					break
				if output:
					ram_latency_vals.append(int(output.strip()))
			stride = stride * 2
		arr_size = arr_size * 2
	ram_latency_highlevel.append(ram_latency_vals)

#print ram_latency_highlevel

def average(l):
    llen = len(l)
    def divide(x): return x / llen
    return map(divide, map(sum, zip(*l)))

avg_ram_latency_vals = average(ram_latency_highlevel)

sheet1 = book.add_sheet("RAM Latency")
sheet1.write(1,1,"RAM Latency")
arr_size = array_size
i=3
for x in range(latency_range):
	sheet1.write(i,1,math.log(arr_size*4,2))
	i=i+1
	arr_size = arr_size * 2
stride = stride_size
j=2
for y in range(latency_range):
	sheet1.write(2,j,math.log(stride*4,2))
	j=j+1
	stride = stride * 2

val = 0
i=3
arr_size = array_size
for x in range(latency_range):
	j=2
	stride = stride_size
	for y in range(latency_range):
		if stride>=arr_size:
			break
		sheet1.write(i,j,int(avg_ram_latency_vals[val]))
		j=j+1
		val=val+1
		stride = stride * 2
	i=i+1
	arr_size = arr_size * 2
'''

#RAM Latency random
latency_range = 17
array_size = 256*4
array_size = array_size / 4
random_start = 10
random_range = 4
ram_latency_highlevel = []
for i in range(num_tests):	
	ram_latency_vals = []
	arr_size = array_size
	for x in range(latency_range):
		random_val = 10
		for y in range(random_range):
			args = ['./ram_latency',str(arr_size),'1','1',str(random_val)]
			process = subprocess.Popen(args, stdout=subprocess.PIPE)
			while True:
				output = process.stdout.readline()
				if output == '' and process.poll() is not None:
					break
				if output:
					ram_latency_vals.append(int(output.strip()))
			random_val = random_val * 10
		arr_size = arr_size * 2
	ram_latency_highlevel.append(ram_latency_vals)

def average(l):
    llen = len(l)
    def divide(x): return x / llen
    return map(divide, map(sum, zip(*l)))

avg_ram_latency_vals = average(ram_latency_highlevel)

sheet1 = book.add_sheet("RAM Latency")
sheet1.write(1,1,"RAM Latency")
arr_size = array_size
i=3
for x in range(latency_range):
	sheet1.write(i,1,math.log(arr_size*4,2))
	i=i+1
	arr_size = arr_size * 2
random_val = random_start
j=2
for y in range(random_range):
	sheet1.write(2,j,random_val)
	j=j+1
	random_val = random_val * 10

val = 0
i=3
for x in range(latency_range):
	j=2
	random_val = random_start
	for y in range(random_range):
		sheet1.write(i,j,int(avg_ram_latency_vals[val]))
		j=j+1
		val=val+1
	i=i+1

book.save("readings.xls")

