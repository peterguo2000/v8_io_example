#define SERVER_PORT 8000
#define MAXLINE 4096
enum IO_TYPE {IO_BLOKING, IO_NON_BLOKING, IO_MUTIPLEXING}; 
class TcpServer {
	public:
		static void start(IO_TYPE ioType);
};
