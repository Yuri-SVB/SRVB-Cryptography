	#Add these lines below 
#  	-D __DBG__																	\
#  	-D __SHOW__																	\
# 	-D __PUT__																	\
	#between 'g++ main.cpp' and '-include $PATH_TO_YSVB_BP' in order respectively 
	#to activate tests (__DBG__) or logs (__SHOW__ and __PUT__)

	#Substitute the first line after '-lgmpxx -lgmp -lm'
	#ie the line beginning with	'-I ../random_input/'
	#by any of the lines bellow:
#-I ../random_input/std/user_seed/		\
#-I ../random_input/std/random_device/	\
#-I ../random_input/std/pseudo_random	\
#-I ../random_input/std/3_layers		\
	
	#in order to choose for different sources of random input. In the
	#1st, you will be asked to enter a string of random characters of your keyboard.
		#Hint: Try inputing strings extrated from secret videos, pictures or audios, stored in safe media, or digests of them.
		#A future version in wich you can automatically input a file of random digits as a random source is on its way.
	#2nd, if your system is capable of, it will produce the true random input for you, otherwise it will prompt an error message;
	#3rd, your system will only produce pseudo random input, based on the time it does so.
		#The program will also skip inputs based on the time each input is given. Since there are lots of hard to measure variables
		#concerning the performance of a given program by each system, there end up being some degree of true randomness on this 
		#option too

g++ main.cpp								\
 	-D __SHOW__								\
 	-D __PUT__								\
 	-lgmpxx -lgmp -lm						\
 	-I ../random_input/std/3_layers/		\
 	-I ../ysvb-bug-proof/					\
 	-I ../integers/							\
 	-I ../decrypt/							\
 	-I ../encrypt/							\
 	-std=gnu++11							\
 	-o key_gen_SRVB