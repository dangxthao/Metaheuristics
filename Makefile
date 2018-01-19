
clean_files1 = Implementation/*_breach* Implementation/{out*,cl*.mat}
clean_files2 = outcmaes* *~
clean_files3 = Implementation/add_pts.m Implementation/Coverage*.m Implementation/test*.m Implementation/





add: 
	make clean; git add ./


commit:
	git commit -m "updated repo"

upload: 
	make add; make commit;  git push

clean:
	rm -rf $(clean_files1) $(clean_files2) $(clean_files3)
