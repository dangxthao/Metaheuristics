
clean_files1 = Implementation/*_breach*
clean_files2 = {outcmaes* *~}






add: 
	make clean; git add ./


commit:
	git commit -m "updated repo"

upload: 
	make add; make commit;  git push

clean:
	rm $(clean_files1) $(clean_files2)
