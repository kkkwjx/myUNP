#pragma once
#include "Common.h"
#include <utility>
class InetAddress;

class Socket:Noncopyable
{
public:
	explicit Socket(int sockfd);
	~Socket();
	Socket(Socket &&rhs)
	 :sockfd_(rhs.sockfd_)
	{
		rhs.sockfd_=-1;
	}
	Socket& operator=(Socket &rhs)
	{
		swap(rhs);
		return *this;
	}
	void swap(Socket &rhs)
	{
		std::swap(sockfd_,rhs.sockfd_);
	}
	int fd() const
	{
		return sockfd_;
	}
	
	void bindOrDie(const InAddress &addr);
	void listenOrDie();
	
	int connect(const InetAddress &addr);
	void shutdownWrite();
	void setReuseAddr(bool on);
	void setTcpNoDelay(bool on);
	InetAddress getLocalAddr() const;
	InetAddress getPeerAddr() const;
	int read(void *buf,int len);
	int write(const void* buf,int len);

	static Socket createTCP();
	static Socket createUDP();
private:
	int sockfd_;
};
