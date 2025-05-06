[![License](https://img.shields.io/badge/license-GPLv2-blue.svg)](LICENSE)
[![Contributions Welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg)](README.md#Contributing)
![GH Action Build Status](https://github.com/mulatinho/sfm/actions/workflows/build.yaml/badge.svg)


Simple File Manager [![Build Status](https://travis-ci.org/mulatinho/sfm.svg?branch=master)](http://travis-ci.org/mulatinho/sfm)
===================

This project is a lightweight file manager written only for fun and profit,
it is written in C with GTK and have some features to interact with remote
(samba and ssh) file systems. Another cool tool that we want to make in future
is the SFM file manager in text console with NCURSES library. Wait for it!

### Some tips for you
* You should not use the last development release now, this is just for 
developers who are interested in contribute, instead download some real 
release in this url:

  https://github.com/mulatinho/sfm/releases

* To install this software please read the INSTALL file.
* To contribute with this software please read the HACKING file.

SCREENSHOTS

![SFM02](https://mulatinho.files.wordpress.com/2015/12/sfm02.png)

![SFM01](https://mulatinho.files.wordpress.com/2015/12/sfm01.png)

![SFM00](https://mulatinho.files.wordpress.com/2015/12/sfm00.png)



### [Contributing](#Contributing)

```
git clone https://github.com/mulatinho/sfm.git
./autogen.sh && ./configure
# edit your changes, and guarantee its working
make
# create a PR and wait for it get merged :-)
