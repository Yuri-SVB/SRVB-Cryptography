	#Add these lines below 
#  	-D __DBG__																	\
#  	-D __SHOW__																	\
# 	-D __PUT__																	\
	#between 'g++ main.cpp' and '-include $PATH_TO_YSVB_BP' in order respectively 
	#to activate tests (__DBG__) or logs (__SHOW__ and __PUT__)

g++ main.cpp				\
 	-D __SHOW__				\
 	-D __PUT__				\
 	-lgmpxx -lgmp -lm		\
 	-I ../ysvb-bug-proof/	\
 	-I ../integers/			\
 	-I ../encrypt/			\
 	-std=gnu++11			\
 	-o decrypt_SRVB