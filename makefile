rev: revenue_pd.o
	g++ -o rev revenue_pd.o
revenue_pd.o: revenue_pd.cpp
	g++ -c revenue_pd.cpp
clean: 
	rm *.o rev