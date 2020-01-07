import os
import * from check_leaks.py
from re import compile, findall
from time import time

g_pattern = compile(r'\d+')

class f:
	one = "flow-one_"
	ten = "flow-ten_"
	thousand = "flow-thousand_"
	big = "big_"
	big_superposition = "big-superposition_"

def create_maps_files(arg, name):
	i = 0;
	while i < 10:
		os.system("./generator " + arg + " > ../maps/" + name + str(i))
		i = i + 1;
	print("\033[32mMaps " + name[:-1] + " created 10 times.\033[0m")

def create_maps(name):
	os.system("clear")
	if name == "all" or name == "--flow-one":
		if not os.path.isfile("../maps/flow-one_0"):
			create_maps_files("--flow-one", f.one)
	if name == "all" or name == "--flow-ten":
		if not os.path.isfile("../maps/flow-ten_0"):
			create_maps_files("--flow-ten", f.ten)
	if name == "all" or name == "--flow-thousand":
		if not os.path.isfile("../maps/flow-thousand_0"):
			create_maps_files("--flow-thousand", f.thousand)
	if name == "all" or name == "--big":
		if not os.path.isfile("../maps/big_0"):
			create_maps_files("--big", f.big)
	if name == "all" or name == "--big-superposition":
		if not os.path.isfile("../maps/big-superposition_0"):
			create_maps_files("--big-superposition", f.big_superposition)
	print()

def choice_maps():
	choice = input("""
		All maps are created 10 times.
		A: All maps
		B: Flow-one
		C: Flow-ten
		D: Flow-thousand
		E: Big
		F: Big-superposition
		G: Check Leaks with 5 maps each
		Type your choice : """)
	if choice == "A" or choice == "a":
		create_maps("all")
		return 1
	elif choice == "B" or choice == "b":
		create_maps("--flow-one")
		return 2
	elif choice == "C" or choice == "c":
		create_maps("--flow-ten")
		return 3
	elif choice == "D" or choice == "d":
		create_maps("--flow-thousand")
		return 4
	elif choice == "E" or choice == "e":
		create_maps("--big")
		return 5
	elif choice == "F" or choice == "f":
		create_maps("--big-superposition")
		return 6
	elif choice == "G" or choice == "g"

	else:
		print("You must only select either A, B, C, D, E, or F")
		print("Please try again")
		choice_maps()
		print('\n')

def launch(name):
	if not os.path.exists("../Result"):
		os.makedirs("../Result")
	i = 0;
	timer = []
	print("\033[32m\tCorrection of " + name[:-1] + " in work.\033[0m")
	while i < 10:
		t1 = time()
		os.system("cat " + "../maps/" + name + str(i) + "| .././lem-in > " + "../Result/result" + name + str(i))
		timer.append(round(time() - t1, 2))
		i = i + 1;
	correction(name, timer)

def correction(name, timer):
	i = 0;
	values = []
	while i < 10:
		with open("../Result/result" + name + str(i), "r") as f:
		    for line in f.readlines():
		    	if (line.startswith("The right solution with ")):
			    	values = findall(g_pattern, line)
		result1 = (("\033[32m" + values[2] + "\033[0m") if int(values[2]) <= int(values[3]) else ("\033[31m" + values[2] + "\033[0m"))
		result2 = (("\033[32m" + values[3] + "\033[0m") if int(values[2]) > int(values[3]) else ("\033[31m" + values[3] + "\033[0m"))
		print(name[:-1] + " files n'" + str(i) + " : " + values[0] + " ant(s) lemin -> " + result1 + " files -> " + result2 + " in " + str(timer[i]) + " sec(s)")
		i = i + 1;
	print()

choice = choice_maps()
if os.path.isfile("../maps/flow-one_0") and (choice == 1 or choice == 2):
	launch(f.one)
if os.path.isfile("../maps/flow-ten_0") and (choice == 1 or choice == 3):
	launch(f.ten)
if os.path.isfile("../maps/flow-thousand_0") and (choice == 1 or choice == 4):
	launch(f.thousand)
if os.path.isfile("../maps/big_0") and (choice == 1 or choice == 5):
	launch(f.big)
if os.path.isfile("../maps/big-superposition_0") and (choice == 1 or choice == 6):
	launch(f.big_superposition)

delete = input("""
	Do you want to delete result directory ?
	type : Yes or No
	""")
if delete == "Y" or delete == "y" or delete == "yes" or delete == "Yes":
	os.system("rm -rf ../Result")
	print("\033[31mResult directory deleted !\033[0m")
elif delete == "N" or delete == "n" or delete == "no" or delete == "No":
	print("\033[32mResult directory has conserved !\033[0m")
else:
	print("\033[31mBad input !\033[0m")

delete = input("""
	Do you want to delete all maps created before ?
	type : Yes or No
	""")
if delete == "Y" or delete == "y" or delete == "yes" or delete == "Yes":
	os.system("rm ../maps/*")
	print("\033[31mMaps deleted !\033[0m")
elif delete == "N" or delete == "n" or delete == "no" or delete == "No":
	print("\033[32mMaps has conserved !\033[0m")
else:
	print("\033[31mBad input !\033[0m")