# SRVB-Cryptography
[Asymmetric Cryptography](https://en.wikipedia.org/wiki/Public-key_cryptography) by [Daniel SANTANA ROCHA](https://www.linkedin.com/in/daniel-santana-rocha-48800439/) and [Yuri da Silva VILLAS BOAS](https://sites.google.com/site/yurisvillasboas/) based on [Quotient Rings of Gaussian Integers](http://math.stackexchange.com/questions/23358/quotient-ring-of-gaussian-integers)


## Welcome to SRVB CryptoSystem!

###### First of all, thank you for your attention, interest, and trust!

SRVB cryptosystems are asymmetric cryptosystems created by Daniel Santana Rocha and Yuri da Silva Villas Boas. Our cryptosystems are sure to be _Simple_ and _Free_, and, by disclosing it to as many people as possible and contributing to [our campaign](https://srvbblog.wordpress.com/), we may confirm they are indeed the first cryptosystems ever created to be at the same time, _Simple, Free AND Reliable_. We strongly recommend you to check out that site, for it has very enjoyable media and sales. If you are lay on this subject, it is also an interesting way to get to know a little bit about cryptography. Be sure to check out [our introductory article](https://www.toptal.com/algorithms/introducing-srvb-cryptosystem) published at [Toptal](https://www.toptal.com/#connect-just-masterly-developers-today) (be sure to check out this awesome company as well!) If, on the other hand, you are not so lay, you might be interested on our [academic paper](https://srvbblog.wordpress.com/about-srvb/) explaining how do SRVB cryptosystems work on details.


## OUR SOFTWARE:

### WHAT DOES IT HAVE?

Our project (as any cryptosystem project does) consists in three programs:

1. The key generating program, contained in the directory `key_gen`;
2. The encrypting program, contained in the directory `encryption`;
3. The decrypting program, contained in the directory `decryption`;

In each case, run the script `make.sh` of the respective directory, and run the resulting executable file with the indicated arguments. Advanced users are encouraged to look into those scripts for customized options on how much logging to see, whether or not activate debug mode, and choose the source of randomness for your key generation and encryption. If you want to get your hands really dirty, and have command on C++. you can also edit the files of the directory `random_input` in your own _secret_ way, thus making one additional layer of uncertainty for any attacker.


### HOW TO USE IT?

#### 1. TO GENERATE A PAIR OF SRVB KEYS...

named `NAME_pri_key.srvb` and `NAME_pub_key.srvb` and whose blocks have `b` BITS (not ~~bytes~~!), of which, `p` BITS (same) are random padding, run the executable `key_gen_SRVB` (resulting from the script `key_gen/make.sh`, that can be run from any directory) with the arguments, `k`, `m`, `p` and `NAME`, in this order, where `k` and `m` are any positive integer numbers whose product equals `b`, and `NAME`, is of course, the string you want to be the name of the keys' files. The typical command would look like this:

`./key_gen_SRVB 32 512 8192 /path/to/John/Smith's/SRVB/John_Smith_2017_JAN`

Where the terminal is supposed to be at the key_gen directory (alternatively, you can, of course, append a relative or absolute path to this file on the the left of its name from else where), and `/path/to/John/Smith's/SRVB/` is to be substituted by any relative or absolute path to the target directory of the resulting pair (conversely, you can, of course, choose to manually move it after having outputted it to the current working directory, in which case, no path is to be added). As a result of successfully running it, you shall see two files in the target directory, namely;

`John_Smith_2017_JAN_pub_key.srvb`, and

`John_Smith_2017_JAN_pri_key.srvb`

that correspond respectively to the input files of the PUBLIC and PRIVATE keys, that are to be passed as arguments respectively to the ENCRYPTION and DECRYPTION programs.


#### 2. TO ENCRYPT A FILE...

named `SECRET_FILE` into another file named `ENCRYPTED_SECRET_FILE`, through a (necessarily) PUBLIC key named, say, `John_Smith_2017_JAN_pub_key.srvb`, located at, say, `/path/to/John/Smith's/SRVB/` directory, change the working directory to the `encrypt` folder of the project directory (or, like in the previous case, append adequate paths to the files) and run 

`./encrypt_SRVB /path/to/John/Smith's/SRVB/John_Smith_2017_JAN_pub_key.srvb SECRET_FILE ENCRYPTED_SECRET_FILE`

The resulting encryption file, named `ENCRYPTED_SECRET_FILE` will be then generated at the working directory (unless, like in the previous case, you append a path to it).


#### 3. TO DECRYPT A FILE...

named, say, `ENCRYPTED_SECRET_FILE` into another file named `DECRYPTED_SECRET_FILE`, through a (necessarily) PRIVATE key (necessarily correspondent to that [necessarily] PUBLIC one used to encrypt the original `SECRET_FILE` in the first place) named, say, `John_Smith_2017_JAN_pri_key.srvb`, located at, say, `/path/to/John/Smith's/SRVB/` directory, change the working directory to the `decrypt'`folder of the project directory (or, like in the previous case, append adequate paths to the files) and run 

`./decrypt_SRVB /path/to/John/Smith's/SRVB/John_Smith_2017_JAN_pri_key.srvb ENCRYPTED_SECRET_FILE DECRYPTED_SECRET_FILE`

The resulting decryption file (equal to the last bit to the original `SECRET_FILE`) named `DECRYPTED_SECRET_FILE` will be then generated at the working directory (unless, like in the previous case, you append a path to the file's name).

So, we are done! Share this with your friends, send them a good PUBLIC key, and use your PRIVATE key to decrypt the messages they send you.


#### CONSTRAINT:

`b` and `p` must satisfy `b > p >= 0` and both be integer __multiples of 8__ (number of bits of a byte), though this last constraint is due just to a technicality that provided more easiness of implementation and possibly will be dropped in future versions.


### RECOMMENDATIONS

#### PREAMBLE

Before you start, it is important to recommend generate, store and manipulate any sensible information in secure medias. We recommend you to use encrypted HD partitions, and external medias like (preferably) DVDs to store private keys and sensible files. If you eventually make a _temporary_ copy any of those to insecure media, make sure you delete them [_in a way it is impossible to recover_](http://askubuntu.com/questions/57572/how-to-delete-files-in-secure-manner).

In the case of key generation and encryption, it is good to use a [TRUE RANDOM](https://en.wikipedia.org/wiki/Random_number_generation#.22True.22_vs._pseudo-random_numbers) or [CRYPTOGRAPHY PSEUDO RANDOM](https://en.wikipedia.org/wiki/Cryptographically_secure_pseudorandom_number_generator) input that, of course, does __NOT__ ~~pass through an insecure channel~~ or ~~comes from an untrusted source (such as https://www.random.org/~~ [nothing personal, fellows, I hope you understand us]).

Keep in mind that the, as well as what happens to chains, _what matters to improve a security system is to strengthen its weakest link_, and the weakest link of any good information security system usually is the _human component_. Problems like corruption, threats, physical theft of information storage devices, ~~leaving one's own work station logged on~~, ~~[weak passwords](https://en.wikipedia.org/wiki/Password_strength#Human-generated_passwords)~~, human error, etc. can jeopardize the secrecy of your informations independently of how good a cryptosystem per se is.

#### PARAMETERS

The block size `b` (where `b = k*m`, just remembering) must be as high as to make any _dictionary attack_ to be unfeasible, and for that `b > 100` (_ie_, higher than 103, since b has to be multiple of 8) would already be more than enough. In order to also make the key itself resistent, we recommend take `(2*m+8*k)` at least as high as __1024__ (benchmark to [RSA](https://en.wikipedia.org/wiki/RSA_(cryptosystem))).

If you think your original message can be _guessed_ (example: the copy of any content that had already been published, a text, or the result of a simple use of a published template), then you should worry about the so called _known message attack_. Fortunately for you, we have already implemented the solution for you, which is to set the parameter `p` to a number as high as what `b` was explained to need to be in the previous paragraph (_ie_, higher than 103). Why? `p` is the number of extra BITS that are randomly set to each block, thus adding to each block a content that can't be to guessed (specially if you use a _true random_ source, as explained two paragraphs above). Since any block can only possibly broken all together, adding those extra dummy bits makes it harder for the actual data to be inapropriately achieved. Check out the excerpts of the source code that relate to the padding and/or read about invertible cryptographic [hash functions](https://en.wikipedia.org/wiki/Hash_function) to know more about it. Anyway, it suffices to know that increasing `p` is a trade off between increasing the [entropy](https://en.wikipedia.org/wiki/Entropy_(computing) (number of independent unknown bits) of the block and increasing the encryption's computational cost and resulting file's size, all by a factor of `b/(b-p)`.

If your file is sure to be a original and unpublished content (like a secret video or audio), but is in a format that leads it to be unbalanced on the number of zeroes and ones. Example, an image file with big portions of black, depending on its format, in which case, the blocks encoding that portions would have lower entropy anyway, moreover, a ratio of the number of zeroes to number of ones that is too far from uniformity in a given block can be detected. It might be interesting to set `p` to a ratio of `b`, just to ensure that the padding resulting message will be balanced on the quantity of ones and zeroes. If you set `p = b/2`, for instance, you guarantee that your entropy will be at least as high as the size of your actual data, and that a significant deviation from 1 to 1 in the zeroes to ones ratio will be virtually impossible to observe.

The modulus of the Gaussian integer `alpha` that each SRVB private key depends on is higher than `2^(2*m+8*k)`. Where `k` and `m` are the key parameters explained above. We recommend the exponent expression to be at least 1024.

#### IN A NUTSHELL

* Make sure that `(2*m+8*k)` is at least 1024;
* Set p to at least 128 to avoid 'known message attack' or;
* Set p to a reasonable ratio of b ensure the bit balancing;

If you are unsure about all that, and/or prefer to play safe, just take `k = 32, m = 512, p = 8192`. This is *very* safe from any reasonable (and some unreasonable) point(s) of view. You can, of course, go beyond that, but, before you think about trying to improve any further, make sure you fully understand and take all the precautions mentioned in the PREAMBLE. Remember: _as well as in a chain, the strength of a cryptosystem equals the strength of its weakest components_.

Above all, never forget that the PRIVATE key is produced and ALWAYS kept OFFLINE in a well secure media, and its correspondent PUBLIC key ALONE is to be published.


### HOW EFFECTIVE IS OUR SYSTEM?

#### THE BLOCKS

As a rough approximation, we suggest you to consider a domestic computer capable of performing 2^10 trials per second (which is clearly an overstatement), and a supercomputer to be 2^30 times more powerful. Consider that an year has about 33 million seconds which is roughly 2^25 seconds. So far, we have 65 bits required for a block to resist a brute force attack for about, on average, 1 year in a very pessimistic scenario (in which a top supercomputer is 100% dedicated full time to break a block for as long as one year). Yet, as we said, we can very easily reach a standard as high as 2 Kbyte, making 8192 bits for actual data plus 8192 more bits of padding (ie, bits that are uniformely distributed, so not to be possible to reduce by means of guessing provided that a true random input is used for them), so we can safely say that, under our recommendations, an SRVB data block is _immune to any brute force attack_.

#### THE KEYS

While SRVB depends on a very abundant class of numbers (those Gaussian integers given by `a+bi` with `a` and `b` coprime, [that have an asymtoptic ratio of 6/π² ~ 60.7%](http://mathoverflow.net/questions/97041/what-is-the-probability-that-two-numbers-are-relatively-prime)), RSA relies on real integer primes, [that get linearly scarse with the number of digits of the numbers](https://en.wikipedia.org/wiki/Prime_number_theorem), and yet, a prime as big as one having 1024 (binary) digits is considered to be a satisfactory one. Thus, a good benchmark would be to set the parameters k and m in such a way that `(2*m + 8*k)` is at least as 1024. Keep in mind that you can easily (and freely!) set them to much higher levels, and on the top of using a number that is much harder to guess, you are also [saving at least one euro](http://www.mappamathics.com/) each time you use it, not to mention the *human risk* involved in involving someone else (_ie_ the seller of this prime number) in your secrets (the very primes that are supposed to be known by you alone) and (not to mention risk of the remittance of this prime to be bugged). In other words, how to actually trust your key maker and your key sender? If you are able to _and with SRVB you are_ avoid this problem at all by making your own keys yourself!

### DEPENDENCIES:

#### GMP

In this version, the project uses GNU Multiple Precision

	https://gmplib.org/

to represent big integers. Make sure to follow the steps indicated in the site above in order to have it installed in your system.


#### YSVB BUG PROOF

If your downloaded project does not contain a directory named 'ysvb-bug-proof', enter the following command 

`git submodule update --init --recursive`

in the project's directory. Alternatively, you also can get it downloaded all at once by entering
	
`git clone --recursive https://github.com/Yuri-SVB/SRVB-Cryptography.git`

### SAMPLES:

Our project already comes with pairs of keys and sample files to be (en/de)crypted. They are located at subdirectories called `lab`, within the directories encrypt and decrypt.
