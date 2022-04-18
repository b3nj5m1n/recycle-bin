
(defun indx? (x y)
  "Convert x and y coordinates to index in flattened list

  Convenience method for converting x and y coordinates to the corresponding
  index in the flattened list storing the sudoku fields. Input is 1-indexed,
  the output is 0-indexed.
  "
  (+ (- x 1) (* (- y 1) 9)))

(defun indx-quad? (x y) 
  "Get a list of all coordinates in a 3x3 square

  Given the x and y coordinates for a cell, returns a list of all coordinates
  within the same square. Input is 1-indexed, the output is 0-indexed.
  "
  (let (result (list))
    (loop for i from 0 to 2
          do (loop for j from 0 to 2
                   do (push (list
                              (+ (* 3 (mod (- x 1) 2)) i)
                              (+ (* 3 (mod (- y 1) 2)) j))
                            result)))
    result))

(defun indx-row? (x y)
  "Get a list of all coordinates in a row

  Given the x and y coordinates for a cell, returns a list of all coordinates
  within the same row. Input is 1-indexed, the output is 0-indexed.
  "
  (let (result (list))
    (loop for i from 0 to 8
          do (push (list i y) result))
    result))

(defun indx-col? (x y)
  "Get a list of all coordinates in a column

  Given the x and y coordinates for a cell, returns a list of all coordinates
  within the same column. Input is 1-indexed, the output is 0-indexed.
  "
  (let (result (list))
    (loop for i from 0 to 8
          do (push (list x i) result))
    result))

(defun valid? (numbers)
  "Test wether the given list of numbers could be valid for sudoku

  Given a list of numbers, return true if there are no repeats in the list,
  and each number is between 1-9
  "
  (let* ((sorted (sort numbers #'<))
         (previous -1))
    (loop for number in sorted
          do (
              if (or (< number 0) (> number 9))
                (return-from valid? NIL)
                (if (= number previous)
                 (return-from valid? NIL)
                 (setq previous number))))
    t))

(defun init-sudoku (transforms))







; (init-sudoku (
;               (1 1 6)
;               (2 1 1)
;               (5 1 2)
;               (2 2 7)
;               (3 2 3)
;               (5 2 4)
;               (6 2 6)
;               (8 2 5)
;               (9 2 2)
;               (1 3 4)
;               (7 3 8)
;               (8 3 6)
;               (3 4 6)
;               (4 4 5)
;               (8 4 9)
;               (1 5 9)
;               (2 5 3)
;               (8 5 8)
;               (9 5 5)
;               (2 6 5)
;               (6 6 7)
;               (7 6 1)
;               (2 7 6)
;               (3 7 4)
;               (9 7 8)
;               (1 8 7)
;               (2 8 9)
;               (4 8 3)
;               (5 8 8)
;               (7 8 5)
;               (8 8 1)
;               (4 9 2)
;               (5 9 6)
;               (8 9 4)
;               (9 9 9)))

