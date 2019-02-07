IN  = data-in
OUT = data-out

target:
	/usr/bin/make -f makefile$T C=$C S=$S

execute:
	/usr/bin/make -f makefile$T execute C=$C S=$S

clean:
	/bin/rm -f *.o *.exe ${IN} ${OUT}
	if pgrep -x ".*.exe"; then\
		killall -r ".*.exe"; /bin/ps -f;\
	fi
