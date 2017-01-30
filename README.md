# SRVB-Cryptography
Asymmetric Encription Algorithm by Daniel SANTANA ROCHA and Yuri da Silva VILLAS BOAS based on complex integers


		Welcome to SRVB CryptoSystem!

First of all, thank you for your attention, interest, and trust!

SRVB cryptosystem is an asymmetric cryptography created by Daniel Santana Rocha and co-authored and implemented by Yuri da Silva Villas Boas. Our cryptosystem is sure to be Simple and Free, and, by disclosing it to as many people as possible and contributing to our campaign

	https://srvbblog.wordpress.com/	

we may confirm it is indeed the first cryptosystem ever created to be at the same time, Simple, Free AND Reliable. We strongly recommend you to check out that site, for it has very enjoyable media and sales. If you are lay on this subject, it is also an interesting way to get to know a little bit about cryptography. If, on the other hand, you are not so lay, you might be interested on our paper explaining how does SRVB cryptography work on details.


		OUR SOFTWARE:

	WHAT DOES IT HAVE?

Our project (as any cryptosystem project does) consists in three programs:

1) The Key generating program, contained in the directory 'key_gen';
2) The Encrypting program, contained in the directory 'encryption';
3) The Decrypting program, contained in the directory 'decryption';

In each case, run the script 'make.sh' of the respective directory, and run the resulting executable file with the indicated arguments.

		HOW TO USE IT?

	1) TO GENERATE A PAIR OF SRVB KEYS...

named 'NAME_pri_key.srvb' and 'NAME_pub_key.srvb' and whose blocks have b BITS (not bytes!), of which, p BITS (same) are random padding, run the executable key_gen_SRVB (resulting from the script ./key_gen/make.sh) with the arguments, k, m, p and 'NAME', in this order, where k and m are any positive integer numbers whose product equals b, and 'NAME', is of course, the string you want to be the name of the keys' files. The typical command would look like this:

	./key_gen_SRVB 32 512 8192 /path/to/John/Smith's/SRVB/John_Smith_2017_JAN

Where the terminal is supposed to be at the key_gen directory (alternatively, you can, of course, append a relative or absolute path to this file on the the left of its name from else where), and '/path/to/John/Smith's/SRVB/' is to be substituted by any relative or absolute path to the target directory of the resulting pair (conversely, you can, of course, choose to manually move it after having outputted it to the current working directory, in which case, no path is to be added). As a result of successfully running it, you shall see two files in the target directory, namely;

	John_Smith_2017_JAN_pub_key.srvb, and
	John_Smith_2017_JAN_pri_key.srvb

that correspond respectively to the input files of the PRIVATE and PUBLIC keys, that are to be passed as arguments respectively to the ENCRYPTION and DECRYPTION programs.


	2) TO ENCRYPT A FILE...

named 'SECRET_FILE' into another file named 'ENCRYPTED_SECRET_FILE', through a (necessarily) PUBLIC key named, say, John_Smith_2017_JAN_pub_key.srvb, located at, say, /path/to/John/Smith's/SRVB/ directory, change the working directory to the 'encrypt' folder of the project directory (or, like in the previous case, append adequate paths to the files) and run 

	./encrypt_SRVB /path/to/John/Smith's/SRVB/John_Smith_2017_JAN_pub_key.srvb SECRET_FILE ENCRYPTED_SECRET_FILE

The resulting encryption file, named 'ENCRYPTED_SECRET_FILE' will be then generated at the working directory (unless, like in the previous case, you append a path to it).


	3) TO DECRYPT A FILE...

named, say, 'ENCRYPTED_SECRET_FILE' into another file named 'DECRYPTED_SECRET_FILE', through a (necessarily) PRIVATE key (necessarily correspondent to that [necessarily] PUBLIC one used to encrypt the original SECRET_FILE in the first place) named, say, John_Smith_2017_JAN_pri_key.srvb, located at, say, /path/to/John/Smith's/SRVB/ directory, change the working directory to the 'decrypt' folder of the project directory (or, like in the previous case, append adequate paths to the files) and run 

	./decrypt_SRVB /path/to/John/Smith's/SRVB/John_Smith_2017_JAN_pri_key.srvb ENCRYPTED_SECRET_FILE DECRYPTED_SECRET_FILE

The resulting decryption file, named 'DECRYPTED_SECRET_FILE' will be then generated at the working directory (unless, like in the previous case, you append a path to the file's name).

So, we are done! Share this with your friends, send them a good PUBLIC key, and use your PRIVATE key to decrypt the messages they send you.


	CONSTRAINT:

b and p must satisfy b > p >= 0 and both be integer multiples of 8 (number of bits of a byte), though this last constraint is due just to a technicality that provided more easiness of implementation and possibly will be dropped in future versions.


		RECOMMENDATIONS

	PREAMBLE

Before you start, it is important to recommend generate, store and manipulate any sensible information in secure medias. We recommend you to use encrypted HD partitions, and external medias like (preferably) DVDs to store private keys and sensible files. If you eventually copy any of those to insecure media, make sure you delete them *in a way it is impossible to recover*.

In the case of key generation and encryption, it is good to use a TRUE RANDOM input that, of course, does NOT pass through an insecure channel or comes from an untrusted source (such as https://www.random.org/).

Keep in mind that the, as well as what happens to chains, what matters to improve a security system is to strengthen its weakest link, and the weakest link of any good information security system usually is the human component. Problems like corruption, threats, physical theft of information storage devices, forgetting to log out, dummy passwords, human error, etc. can jeopardize your secrecy independently of how good a cryptosystem per se is.

	PARAMETERS

The block size 'b' (where b = k*m, just remembering) must be as high as to make any 'dictionary attack' to be unfeasible, and for that b > 100 (ie, highre than 103, for b has to be multiple of 8) would already be more than enough. In order to also make the key itself resistent, we recommend take (2*m+8*k) at least as high as 1024 (benchmark to RSA).

If you think your original message can be guessed (example: the copy of any content that had already been published, or a text, or the result of a simple use of a published template), then you should worry about the so called 'known message attack'. Thankfully for you, we have already implemented the solution for you, which is to set the parameter p to a number as high as what b was explained to need to be in the previous paragraph (ie, higher than 103). Why? p is the number of extra BITS that are randomly set to each block, thus adding to each block a content that can't be to guessed (specially if you use a true random source, as explained two paragraphs above). Since any block can only possibly broken all together, adding those extra dummy bits makes it harder for the actual data to be inapropriately achieved. Check out the excerpts of the source code that relate to the padding and/or read about *invertible cryptographic hash functions* to know more about it. Anyway, it suffices to know that increasing p is a trade off between increasing bits of uncertainty (for the attacker) and the cost computational cost and resulting file's size, both by a factor of b/(b-p).

If your file is sure to be a original and unpublished content, but is in a format that leads it to be unbalanced on the number of 1's and 0's (example, an image file with a big portion of black, depending on its format), it might be interesting to set p to a ratio of b, just to ensure that the padding resulting message will be balanced on the quantity of ones and zeroes. If you set p = p/2, for instance, you guarantee that, your distribution of quantity of 0's and 1's will be close to the normal (technically speaking, close to binomial of parameters 1/2 and b).

The prime Gaussian integer alpha that each SRVB private key depends on is higher than 2^(2*m+8*k). Where k and m are the key parameters explained above. We recommend the exponent expression to be at least 1024.

	IN A NUTSHELL

Make sure that (2*m+8*k) is at least 1024;
Set p to at least 128 to avoid 'known message attack' or;
Set p to a reasonable ratio of b ensure the bit balancing;

If you are unsure about all that, and/or prefer to play safe, just take k = 32, m = 512, p = 8192. That is *very* safe in any reasonable (and some unreasonable) aspects. You can, of course, go beyond that, but, before you think about trying to improve any further, make sure you understand and take all the precautions mentioned in the PREAMBLE.

Above all, never forget that the PRIVATE key is produced and ALWAYS kept OFFLINE, and its correspondent PUBLIC key ALONE is to be published.


		HOW EFFECTIVE IS OUR SYSTEM?

	THE BLOCKS

As a rough approximation, we suggest you to consider a domestic computer capable of performing 2^10 trials per second (which is clearly an overstatement), and a supercomputer to be 2^30 times more powerful. Consider that an year has about 33 million seconds which is roughly 2^25 seconds. So far, we have 65 bits required for a block to resist a brute force attack for about, on average, 1 year in a very pessimistic scenario (in which a top supercomputer is 100% dedicated full time to break a block for as long as one year). Yet, as we said, we can very easily reach a standard as high as 2 Kbyte, making 8192 bits for actual data plus 8192 more bits of padding (ie, bits that are uniformely distributed, so not to be possible to reduce by means of guessing provided that a true random input is used for them), so we can safely say that our data blocks are immune to any brute force attack.

	THE KEYS

While the prime Gaussian integers, which SRVB keys depends on, are far more abundant and less studied than real integer primes, RSA relies on the latter, and yet, a prime as big as one having 1024 (binary) digits is considered to be a satisfactory one. Thus, a good benchmark would be to set the parameters k and m in such a way that (2*m + 8*k) + 8 is at least as 1024. Keep in mind that you can easily (and freely!) set them to much higher levels, and on the top of using a number that is much harder to guess, you are also saving at least one euro each time you use it,

see http://www.mappamathics.com/

not to mention the *human risk* involved in involving someone else (ie.: the seller of this prime number) in your secrets (the very primes that are supposed to be known by you alone) and sending the key to you. In other words, how to actually trust your key maker and your key sender? If you are able to _and with SRVB you are_ avoid this problem at all by making your own keys yourself!

		DEPENDENCIES:

	GMP

In this version, the project uses GNU Multiple Precision

	https://gmplib.org/

to represent big integers. Make sure to follow the steps indicated in the site above in order to have it installed in your system.


	YSVB BUG PROOF

If your downloaded project does not contain a directory named 'ysvb-bug-proof', enter the following command 

	git submodule update --init --recursive

in the project's directory. Alternatively, you also can get it downloaded all at once by entering

	git clone --recursive https://github.com/Yuri-SVB/ysvb-bug-proof


		SAMPLES:

Our project already comes with pairs of keys and sample files to be (en/de)crypted. They are located at subdirectories called 'lab', within the directories encrypt and decrypt.
