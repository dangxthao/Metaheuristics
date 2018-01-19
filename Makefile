







add: 
	make clean; git add ./


commit:
	git commit -m "updated repo"

upload: 
	make add; make commit;  git push

clean:
	rm outcmaes* *~
