	#Add these lines below 
#  	-D __DBG__																	\
#  	-D __SHOW__																	\
# 	-D __PUT__																	\
	#between 'g++ main.cpp' and '-include $PATH_TO_YSVB_BP' in order respectively 
	#to activate tests (__DBG__) or logs (__SHOW__ and __PUT__)

DC_PATH="`dirname \"$0\"`"              # relative
DC_PATH="`( cd \"$DC_PATH\" && pwd )`"  # absolutized and normalized
if [ -z "$DC_PATH" ] ; then
	echo "Failed to access the folder key_gen directory"
	exit 1  # fail
fi

g++ $DC_PATH"/main.cpp"				\
 	-D __SHOW__				\
 	-D __PUT__				\
 	-lgmpxx -lgmp -lm		\
 	-I $DC_PATH"/../ysvb-bug-proof/"	\
 	-I $DC_PATH"/../integers/"			\
 	-I $DC_PATH"/../encrypt/"			\
 	-std=gnu++11			\
 	-o $DC_PATH"/decrypt_SRVB"
