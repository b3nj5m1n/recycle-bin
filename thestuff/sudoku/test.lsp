(load "sudoku.lsp")

(fiveam:test test-indx?
             (fiveam:is (= 0 (indx? 0 0)))
             (fiveam:is (= 41 (indx? 5 4))))

(fiveam:test test-valid?
             (fiveam:is (not (valid? (list -1 2 3))))
             (fiveam:is (not (valid? (list 2 2 3))))
             (fiveam:is (not (valid? (list 12 2 3))))
             (fiveam:is (not (valid? (list nil 2 nil 3 nil 2))))
             (fiveam:is (valid? (list 5 2 3)))
             (fiveam:is (valid? (list 5 2 3 7 4 1 9 8)))
             (fiveam:is (valid? (list 5 nil 3 7 nil 1 9 nil))))

(fiveam:test test-solve?
             (fiveam:is (equal
                          (solve-sudoku (list 6 1 NIL NIL 5 2 NIL NIL NIL NIL 7 3 NIL 4 6 NIL 5 2 4 NIL
                                          NIL NIL NIL NIL 8 6 NIL NIL NIL 6 5 NIL NIL NIL 9 NIL 9 3
                                          NIL NIL NIL NIL NIL 8 5 NIL 5 NIL NIL NIL 7 1 NIL NIL NIL
                                          6 4 NIL NIL NIL NIL NIL 8 7 9 NIL 3 8 NIL 5 1 NIL NIL NIL
                                          NIL 2 6 NIL NIL 4 9))
                          (list 6 1 9 8 5 2 4 7 3 8 7 3 1 4 6 9 5 2 4 2 5 9 7 3 8 6 1 1 4
                           6 5 3 8 2 9 7 9 3 7 4 2 1 6 8 5 2 5 8 6 9 7 1 3 4 5 6 4 7
                           1 9 3 2 8 7 9 2 3 8 4 5 1 6 3 8 1 2 6 5 7 4 9))))

