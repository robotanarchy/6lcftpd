# 6lcftpd
Six Lines of Config FTP Daemon [(example config)](https://github.com/robotanarchy/6lcftpd/blob/master/6lcftpd.sample.cfg)

This is just my little test project to get started with C++.

Right now it's wrapping `SDL2_net` (tried asio, but whoa, that's so much bloat there ...). It is multithreaded, valgrind tested and creates a control socket to chat with FileZilla and other clients. It can not list files or do anything useful yet, so you should probably not use it in production right now.
