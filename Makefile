CC= g++ -g
make:
	$(CC) consumer.cc -o consumer
	$(CC) producer.cc -o producer
	
