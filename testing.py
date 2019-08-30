import os

#TEST INIT
print ("Runing the tests:")
os.system("rm test_results.txt")
Result = "V"
Colored = "\033[92mV"
test_command = ""
test_results = open("test_results.txt", "x")
std = open(1, "r")


# # TEST SCHEME
# test = "INSERT_TEST"  #MODIFY INSERT_TEXT by the command line
# test_results.write("Test X : " + test + "\n") #MODIFY X by the test number
# test_command = "./ft_ssl md5 " + test + "  > my.txt && md5 " + test + " > real.txt && diff my.txt real.txt > diff"
# os.system(test_command)
# if (os.stat("diff").st_size != 0):
# 	Result = "X"
# 	Color = "\033[91mX"
# else:
# 	Result = "V"
# 	Colored = "\033[92mV"
# print (Colored, end = '')
# test_results.write("Test X: " + Result + "\n\n") #MODIFY X by the test number

# TEST 1
test="-r -s ok"
test_results.write("Test 1 : " + test + "\n")
test_command = "./ft_ssl md5 " + test + "  > my.txt && md5 " + test + " > real.txt && diff my.txt real.txt > diff"
os.system(test_command)
if (os.stat("diff").st_size != 0):
	Result = "X"
	Color = "\033[91mX"
else:
	Result = "V"
	Colored = "\033[92mV"
print (Colored, end = '')
test_results.write("Test 1: " + Result + "\n\n")

# TEST 2
test = "-r -s ok makefile"
test_results.write("Test 2 : " + test + "\n")
test_command = "./ft_ssl md5 " + test + "  > my.txt && md5 " + test + " > real.txt && diff my.txt real.txt > diff"
os.system(test_command)
if (os.stat("diff").st_size != 0):
	Result = "X"
	Color = "\033[91mX"
else:
	Result = "V"
	Colored = "\033[92mV"
print (Colored, end = '')
test_results.write("Test 2: " + Result + "\n\n")

# TEST 3
test = " -s ok makefile"
test_results.write("Test 3 : " + test + "\n")
test_command = "./ft_ssl md5 " + test + "  > my.txt && md5 " + test + " > real.txt && diff my.txt real.txt > diff"
os.system(test_command)
if (os.stat("diff").st_size != 0):
	Result = "X"
	Color = "\033[91mX"
else:
	Result = "V"
	Colored = "\033[92mV"
print (Colored, end = '')
test_results.write("Test 3: " + Result + "\n\n")

# TEST 4
test = "-q -s ok makefile"
test_results.write("Test 4 : " + test + "\n")
test_command = "./ft_ssl md5 " + test + "  > my.txt && md5 " + test + " > real.txt && diff my.txt real.txt > diff"
os.system(test_command)
if (os.stat("diff").st_size != 0):
	Result = "X"
	Color = "\033[91mX"
else:
	Result = "V"
	Colored = "\033[92mV"
print (Colored, end = '')
test_results.write("Test 4: " + Result + "\n\n")

# TEST 5
test = "-q -r -s ok makefile"
test_results.write("Test 5 : " + test + "\n")
test_command = "./ft_ssl md5 " + test + "  > my.txt && md5 " + test + " > real.txt && diff my.txt real.txt > diff"
os.system(test_command)
if (os.stat("diff").st_size != 0):
	Result = "X"
	Color = "\033[91mX"
else:
	Result = "V"
	Colored = "\033[92mV"
print (Colored)
test_results.write("Test 5: " + Result + "\n\n")


#TEST END
os.system("rm my.txt && rm real.txt && rm diff")
test_results.close()
print()
