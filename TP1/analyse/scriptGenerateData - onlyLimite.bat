setlocal EnableExtensions EnableDelayedExpansion






for %%I in ("E:\ecole\inf8775\INF8775-master\TP1\ex\s2-t7-n5-r1\ex2*") do (
	for %%J in ("E:\ecole\inf8775\INF8775-master\TP1\ex\s2-t7-n5-r1\ex2*") do (
		E:\ecole\inf8775\INF8775-master\TP1\cmake-build-debug\INF8775_tp1.exe "%%I" "%%J" strassenAvecLimite t >> test.csv
		echo ,ex2,strassenAvecLimite >> test.csv
	)
)
for %%I in ("E:\ecole\inf8775\INF8775-master\TP1\ex\s2-t7-n5-r1\ex3*") do (
	for %%J in ("E:\ecole\inf8775\INF8775-master\TP1\ex\s2-t7-n5-r1\ex3*") do (
		E:\ecole\inf8775\INF8775-master\TP1\cmake-build-debug\INF8775_tp1.exe "%%I" "%%J" strassenAvecLimite t >> test.csv
		echo ,ex3,strassenAvecLimite >> test.csv
	)
)
for %%I in ("E:\ecole\inf8775\INF8775-master\TP1\ex\s2-t7-n5-r1\ex4*") do (
	for %%J in ("E:\ecole\inf8775\INF8775-master\TP1\ex\s2-t7-n5-r1\ex4*") do (
		E:\ecole\inf8775\INF8775-master\TP1\cmake-build-debug\INF8775_tp1.exe "%%I" "%%J" strassenAvecLimite t >> test.csv
		echo ,ex4,strassenAvecLimite >> test.csv
	)
)
for %%I in ("E:\ecole\inf8775\INF8775-master\TP1\ex\s2-t7-n5-r1\ex5*") do (
	for %%J in ("E:\ecole\inf8775\INF8775-master\TP1\ex\s2-t7-n5-r1\ex5*") do (
		E:\ecole\inf8775\INF8775-master\TP1\cmake-build-debug\INF8775_tp1.exe "%%I" "%%J" strassenAvecLimite t >> test.csv
		echo ,ex5,strassenAvecLimite >> test.csv
	)
)
for %%I in ("E:\ecole\inf8775\INF8775-master\TP1\ex\s2-t7-n5-r1\ex6*") do (
	for %%J in ("E:\ecole\inf8775\INF8775-master\TP1\ex\s2-t7-n5-r1\ex6*") do (
		E:\ecole\inf8775\INF8775-master\TP1\cmake-build-debug\INF8775_tp1.exe "%%I" "%%J" strassenAvecLimite t >> test.csv
		echo ,ex6,strassenAvecLimite >> test.csv
	)
)
for %%I in ("E:\ecole\inf8775\INF8775-master\TP1\ex\s2-t7-n5-r1\ex7*") do (
	for %%J in ("E:\ecole\inf8775\INF8775-master\TP1\ex\s2-t7-n5-r1\ex7*") do (
		E:\ecole\inf8775\INF8775-master\TP1\cmake-build-debug\INF8775_tp1.exe "%%I" "%%J" strassenAvecLimite t >> test.csv
		echo ,ex7,strassenAvecLimite >> test.csv
	)
)
for %%I in ("E:\ecole\inf8775\INF8775-master\TP1\ex\s2-t7-n5-r1\ex8*") do (
	for %%J in ("E:\ecole\inf8775\INF8775-master\TP1\ex\s2-t7-n5-r1\ex8*") do (
		E:\ecole\inf8775\INF8775-master\TP1\cmake-build-debug\INF8775_tp1.exe "%%I" "%%J" strassenAvecLimite t >> test.csv
		echo ,ex8,strassenAvecLimite >> test.csv
	)
)
endlocal