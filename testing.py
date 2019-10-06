import os

#TEST INIT
print ("Runing the tests:")
os.system("rm test_results.txt")
Result = "V"
Colored = "\033[92mV"
Prompt = ""
test_command = ""
test_results = open("test_results.txt", "x")
std = open(1, "r")


# # TEST SCHEME
# test_name = "X" #MODIFY X by the test name
# test = "INSERT_TEST"  #MODIFY INSERT_TEXT by the command line
# Prompt = ""
# test_results.write("Test " + test_name + " : " + test)
# if (Prompt != ""):
# 	test_results.write(" | " + Prompt)
# test_results.write("\n")
# test_command = Prompt + "./ft_ssl md5 " + test + "  > my.txt && " + Prompt + "md5 " + test + " > real.txt && diff my.txt real.txt > diff"
# os.system(test_command)
# if (os.stat("diff").st_size == 0):
# 	Result = "V"
# 	Colored = "\033[92mV"
# else:
# 	Result = "X"
# 	Colored = "\033[91mX"
# print (Colored, end = '')
# test_results.write("Test " + test_name + " : " + Result + "\n\n")

# # TEST SCHEME BASE
# test_name = "X" #MODIFY X by the test name
# test = "INSERT_CMD"  #MODIFY INSERT_CMD by the command line
# Prompt = "INSERT_PROMPT" #MODIFY INSERT_PROMPT by the text to encrypt/decrypt
# test_results.write("Test " + test_name + " : " + test)
# test_results.write(" | " + Prompt)
# test_results.write("\n")
# Prompt = "echo \"" + Prompt + "\" | "
# test_command = Prompt + "./ft_ssl base64 " + test + "  > my.txt && " + Prompt + "openssl base64 " + test + " > real.txt && diff my.txt real.txt > diff"
# os.system(test_command)
# if (os.stat("diff").st_size == 0):
# 	Result = "V"
# 	Colored = "\033[92mV"
# else:
# 	Result = "X"
# 	Colored = "\033[91mX"
# print (Colored, end = '')
# test_results.write("Test " + test_name + " : " + Result + "\n\n")

# TEST FAIL
test="-r -s ok"
Prompt = ""
test_results.write("Test FAIL : " + "\n")
test_command = Prompt + "./ft_ssl md5 " + test + " makefile > my.txt &&" + Prompt +  "md5 " + test + " > real.txt && diff my.txt real.txt > diff"
os.system(test_command)
if (os.stat("diff").st_size == 0):
	Result = "V"
	Colored = "\033[92mV"
else:
	Result = "X"
	Colored = "\033[91mX"
print (Colored, end = '')
test_results.write("Test FAIL : " + Result + "\n\n")

# TEST FAIL II
test_name = "FAIL II" #MODIFY X by the test number
test = "-r -s ok makefile -s ok"  #MODIFY INSERT_TEXT by the command line
Prompt = ""
test_results.write("Test " + test_name + " : " + test)
if (Prompt != ""):
	test_results.write(" | " + Prompt)
test_results.write("\n")
test_command = Prompt + "./ft_ssl md5 " + test + "  > my.txt && " + Prompt + "md5 " + test + " > real.txt"
os.system(test_command)
os.system("diff my.txt real.txt > diff")
if (os.stat("diff").st_size == 0):
	Result = "V"
	Colored = "\033[92mV"
else:
	Result = "X"
	Colored = "\033[91mX"
print (Colored, end = '')
test_results.write("Test " + test_name + " : " + Result + "\n\n")

# TEST VALID
test="-r -s ok"
test_results.write("Test VALID : " + "\n")
test_command = "./ft_ssl md5 " + test + "  > my.txt && md5 " + test + " > real.txt && diff my.txt real.txt > diff"
os.system(test_command)
if (os.stat("diff").st_size == 0):
	Result = "V"
	Colored = "\033[92mV"
else:
	Result = "X"
	Colored = "\033[91mX"
print (Colored, end = '')
test_results.write("Test VALID : " + Result + "\n\n")

# TEST 1
test="-r -s ok"
test_results.write("Test 1 : " + test + "\n")
test_command = "./ft_ssl md5 " + test + "  > my.txt && md5 " + test + " > real.txt && diff my.txt real.txt > diff"
os.system(test_command)
if (os.stat("diff").st_size == 0):
	Result = "V"
	Colored = "\033[92mV"
else:
	Result = "X"
	Colored = "\033[91mX"
print (Colored, end = '')
test_results.write("Test 1 : " + Result + "\n\n")

# TEST 2
test = "-r -s ok makefile"
test_results.write("Test 2 : " + test + "\n")
test_command = "./ft_ssl md5 " + test + "  > my.txt && md5 " + test + " > real.txt && diff my.txt real.txt > diff"
os.system(test_command)
if (os.stat("diff").st_size == 0):
	Result = "V"
	Colored = "\033[92mV"
else:
	Result = "X"
	Colored = "\033[91mX"
print (Colored, end = '')
test_results.write("Test 2 : " + Result + "\n\n")

# TEST 3
test = "-s ok makefile"
test_results.write("Test 3 : " + test + "\n")
test_command = "./ft_ssl md5 " + test + "  > my.txt && md5 " + test + " > real.txt && diff my.txt real.txt > diff"
os.system(test_command)
if (os.stat("diff").st_size == 0):
	Result = "V"
	Colored = "\033[92mV"
else:
	Result = "X"
	Colored = "\033[91mX"
print (Colored, end = '')
test_results.write("Test 3 : " + Result + "\n\n")

# TEST 4
test = "-q -s ok makefile"
test_results.write("Test 4 : " + test + "\n")
test_command = "./ft_ssl md5 " + test + "  > my.txt && md5 " + test + " > real.txt && diff my.txt real.txt > diff"
os.system(test_command)
if (os.stat("diff").st_size == 0):
	Result = "V"
	Colored = "\033[92mV"
else:
	Result = "X"
	Colored = "\033[91mX"
print (Colored, end = '')
test_results.write("Test 4 : " + Result + "\n\n")

# TEST 5
test = "-q -r -s ok makefile"
test_results.write("Test 5 : " + test + "\n")
test_command = "./ft_ssl md5 " + test + "  > my.txt && md5 " + test + " > real.txt && diff my.txt real.txt > diff"
os.system(test_command)
if (os.stat("diff").st_size == 0):
	Result = "V"
	Colored = "\033[92mV"
else:
	Result = "X"
	Colored = "\033[91mX"
print (Colored, end = '')
test_results.write("Test 5 : " + Result + "\n\n")

# TEST PROMPT
test = "-p"  #MODIFY INSERT_TEXT by the command line
Prompt = "ok"
test_results.write("Test PROMPT : " + test) #MODIFY X by the test number
if (Prompt != ""):
	test_results.write(" | " + Prompt)
Prompt = "echo \"" + Prompt + "\" | "
test_results.write("\n")
test_command = Prompt + "./ft_ssl md5 " + test + "  > my.txt && " + Prompt + "md5 " + test + " > real.txt && diff my.txt real.txt > diff"
os.system(test_command)
if (os.stat("diff").st_size == 0):
	Result = "V"
	Colored = "\033[92mV"
else:
	Result = "X"
	Colored = "\033[91mX"
print (Colored, end = '')
test_results.write("Test PROMPT : " + Result + "\n\n") #MODIFY X by the test number

# TEST 6
test = "-r -s ok"  #MODIFY INSERT_TEXT by the command line
Prompt = ""
test_results.write("Test 6 : " + test) #MODIFY X by the test number
if (Prompt != ""):
	test_results.write(" | " + Prompt)
test_results.write("\n")
test_command = Prompt + "./ft_ssl md5 " + test + "  > my.txt && " + Prompt + "md5 " + test + " > real.txt && diff my.txt real.txt > diff"
os.system(test_command)
if (os.stat("diff").st_size == 0):
	Result = "V"
	Colored = "\033[92mV"
else:
	Result = "X"
	Colored = "\033[91mX"
print (Colored, end = '')
test_results.write("Test 6 : " + Result + "\n\n") #MODIFY X by the test number

# TEST 7
test = "-r -s ok -q"  #MODIFY INSERT_TEXT by the command line
Prompt = ""
test_results.write("Test 7 : " + test) #MODIFY X by the test number
if (Prompt != ""):
	test_results.write(" | " + Prompt)
test_results.write("\n")
test_command = Prompt + "./ft_ssl md5 " + test + "  > my.txt && " + Prompt + "md5 " + test + " > real.txt && diff my.txt real.txt > diff"
os.system(test_command)
if (os.stat("diff").st_size == 0):
	Result = "V"
	Colored = "\033[92mV"
else:
	Result = "X"
	Colored = "\033[91mX"
print (Colored, end = '')
test_results.write("Test 7 : " + Result + "\n\n") #MODIFY X by the test number

# TEST 7
test_name = "8" #MODIFY X by the test number
test = "-r -s ok -q"  #MODIFY INSERT_TEXT by the command line
Prompt = ""
test_results.write("Test " + test_name + " : " + test)
if (Prompt != ""):
	test_results.write(" | " + Prompt)
test_results.write("\n")
test_command = Prompt + "./ft_ssl md5 " + test + "  > my.txt && " + Prompt + "md5 " + test + " > real.txt && diff my.txt real.txt > diff"
os.system(test_command)
if (os.stat("diff").st_size == 0):
	Result = "V"
	Colored = "\033[92mV"
else:
	Result = "X"
	Colored = "\033[91mX"
print (Colored, end = '')
test_results.write("Test " + test_name + " : " + Result + "\n\n")

# TEST 9
test_name = "9"
test = "ok"
Prompt = ""
test_results.write("Test " + test_name + " : " + test)
if (Prompt != ""):
	test_results.write(" | " + Prompt)
test_results.write("\n")
test_command = Prompt + "./ft_ssl md5 " + test + "  > my.txt && " + Prompt + "md5 " + test + " > real.txt && diff my.txt real.txt > diff"
os.system(test_command)
if (os.stat("diff").st_size == 0):
	Result = "V"
	Colored = "\033[92mV"
else:
	Result = "X"
	Colored = "\033[91mX"
print (Colored, end = '')
test_results.write("Test " + test_name + " : " + Result + "\n\n")

# TEST 1 BASE64
test_name = "1 base64" #MODIFY X by the test name
test = "-d"  #MODIFY INSERT_TEXT by the command line
Prompt = "b2sK"
test_results.write("Test " + test_name + " : " + test)
test_results.write(" | " + Prompt)
test_results.write("\n")
Prompt = "echo \"" + Prompt + "\" | "
test_command = Prompt + "./ft_ssl base64 " + test + "  > my.txt && " + Prompt + "openssl base64 " + test + " > real.txt && diff my.txt real.txt > diff"
os.system(test_command)
if (os.stat("diff").st_size == 0):
	Result = "V"
	Colored = "\033[92mV"
else:
	Result = "X"
	Colored = "\033[91mX"
print (Colored, end = '')
test_results.write("Test " + test_name + " : " + Result + "\n\n")

# TEST 1 BASE64
test_name = ">64 base64" #MODIFY X by the test name
test = "-d"  #MODIFY INSERT_TEXT by the command line
Prompt = "TkFNRSA9IGZ0X3NzbAoKQ0MgPSBnY2MKRkxBR1MgPSAtV2FsbCAtV2V4dHJhIC1XZXJyb3IgLU9mYXN0CgpJTkNMVURFUyA9IGluY2x1ZGVzCgpPQkpfUEFUSCA9IG9iagoKU1JDUyA9CW1haW4uYyBcCgkJcGFyc2VyLmMgXAoJCWRpc3BsYXkuYyBcCgkJ"
test_results.write("Test " + test_name + " : " + test)
test_results.write(" | " + Prompt)
test_results.write("\n")
Prompt = "echo \"" + Prompt + "\" | "
test_command = Prompt + "./ft_ssl base64 " + test + "  > my.txt && " + Prompt + "openssl base64 " + test + " > real.txt && diff my.txt real.txt > diff"
os.system(test_command)
if (os.stat("diff").st_size == 0):
	Result = "V"
	Colored = "\033[92mV"
else:
	Result = "X"
	Colored = "\033[91mX"
print (Colored, end = '')
test_results.write("Test " + test_name + " : " + Result + "\n\n")

#TEST END
os.system("rm my.txt && rm real.txt && rm diff")
test_results.close()
print()
