(load "sudoku")

(fiveam:test test-indx?
  (fiveam:is (= 0 (indx? 1 1)))
  (fiveam:is (= 31 (indx? 5 4))))
  
(fiveam:test test-valid?
  (fiveam:is (not (valid? (list -1 2 3))))
  (fiveam:is (not (valid? (list 2 2 3))))
  (fiveam:is (not (valid? (list 12 2 3))))
  (fiveam:is (valid? (list 5 2 3)))
  (fiveam:is (valid? (list 5 2 3 7 4 1 9 8))))
  
