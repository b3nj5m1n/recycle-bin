
(defun indx? (x y)
  "Convert x and y coordinates to index in flattened list

  Convenience method for converting x and y coordinates to the corresponding
  index in the flattened list storing the sudoku fields.
  "
  (+ x (* y 9)))

(defun indx-quad? (x y) 
  "Get a list of all coordinates in a 3x3 square

  Given the x and y coordinates for a cell, returns a list of all coordinates
  within the same square.
  "
  (let (result (list))
    (loop for i from 0 to 2
          do (loop for j from 0 to 2
                   do (push (list
                              (+ (* 3 (nth-value 0 (floor x 3))) i)
                              (+ (* 3 (nth-value 0 (floor y 3))) j))
                            result)))
    result))

(defun indx-row? (x y)
  "Get a list of all coordinates in a row

  Given the x and y coordinates for a cell, returns a list of all coordinates
  within the same row.
  "
  (let (result (list))
    (loop for i from 0 to 8
          do (push (list i y) result))
    result))

(defun indx-col? (x y)
  "Get a list of all coordinates in a column

  Given the x and y coordinates for a cell, returns a list of all coordinates
  within the same column.
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
  (let* ((sorted (sort (remove nil numbers) #'<))
         (previous -1))
    (loop for number in sorted
          do (
              if (or (< number 0) (> number 9))
                (return-from valid? NIL)
                (if (= number previous)
                 (return-from valid? NIL)
                 (setq previous number))))
    t))

(defun coordinate-list? (coordinates grid)
  "Test wether the given list of coordinates could be valid for sudoku
  "
  (mapcar (lambda (e) (destructuring-bind (x y) e (nth (indx? x y) grid))) coordinates))
  

(defun choice-valid? (x y grid)
  "Test wether the number at the given coordinates makes sense
  "
  (let ((quad (indx-quad? x y))
        (row (indx-row? x y))
        (col (indx-col? x y)))
    (if (not (valid? (coordinate-list? quad grid)))
       (return-from choice-valid? NIL)
       (if (not (valid? (coordinate-list? row grid)))
          (return-from choice-valid? NIL)
          (if (not (valid? (coordinate-list? col grid)))
             (return-from choice-valid? NIL)
             t)))))

(defun init-sudoku (transforms)
  (let ((sudoku (make-list 81)))
    (loop for transform in transforms
      do (
          setf (nth (indx? (- (first transform) 1) (- (second transform) 1)) sudoku) (third transform)))
   sudoku))

(defun solve-sudoku (grid lol)
  (if (not (position nil grid))
    (return-from solve-sudoku grid))
  (defvar result)
  (if (position nil grid)
    (let* ((indx (position nil grid))
           (x (mod indx 9))
           (y (nth-value 0 (floor (- indx x) 9))))
        (loop named theloop for i from 1 to 9
          do (let ((new-grid (copy-list grid)))
               (setf (nth indx new-grid) i)
               (screen:with-window (screen:clear-window screen:*window*))
               (print-sudoku new-grid)
               ; (format t "~% x = ~d y = ~d i = ~2d ~%" x y i)
               ; (format t "~% lol = ~d ~%" lol)
               (if (choice-valid? x y new-grid)
                   (let ((computed (solve-sudoku new-grid (+ lol 1))))
                       (if computed
                         (return-from solve-sudoku computed)))))))))

(defun print-sudoku (grid)
  (let ((g (mapcar (lambda (x) (
                                if (null x) 
                                 "·"
                                 x))
                   grid)))
      (format t "~%┏━━━━━━━┳━━━━━━━┳━━━━━━━┓~%")
      (loop for i from 0 to 8
                 do (format t "┃ ~d ~d ~d ┃ ~d ~d ~d ┃ ~d ~d ~d ┃"
                            (nth (indx? 0 i) g)
                            (nth (indx? 1 i) g)
                            (nth (indx? 2 i) g)
                            (nth (indx? 3 i) g)
                            (nth (indx? 4 i) g)
                            (nth (indx? 5 i) g)
                            (nth (indx? 6 i) g)
                            (nth (indx? 7 i) g)
                            (nth (indx? 8 i) g))
                (if (= 0 (mod (+ i 1) 3))
                  (if (= 8 i)
                    (format t "~%┗━━━━━━━┻━━━━━━━┻━━━━━━━┛~%")
                    (format t "~%┣━━━━━━━╋━━━━━━━╋━━━━━━━┫~%"))
                  (fresh-line))))
  t)
  

(defparameter grid (init-sudoku (list
                                 (list 1 1 6)
                                 (list 2 1 1)
                                 (list 5 1 5)
                                 (list 6 1 2)
                                 (list 2 2 7)
                                 (list 3 2 3)
                                 (list 5 2 4)
                                 (list 6 2 6)
                                 (list 8 2 5)
                                 (list 9 2 2)
                                 (list 1 3 4)
                                 (list 7 3 8)
                                 (list 8 3 6)
                                 (list 3 4 6)
                                 (list 4 4 5)
                                 (list 8 4 9)
                                 (list 1 5 9)
                                 (list 2 5 3)
                                 (list 8 5 8)
                                 (list 9 5 5)
                                 (list 2 6 5)
                                 (list 6 6 7)
                                 (list 7 6 1)
                                 (list 2 7 6)
                                 (list 3 7 4)
                                 (list 9 7 8)
                                 (list 1 8 7)
                                 (list 2 8 9)
                                 (list 4 8 3)
                                 (list 5 8 8)
                                 (list 7 8 5)
                                 (list 8 8 1)
                                 (list 4 9 2)
                                 (list 5 9 6)
                                 (list 8 9 4)
                                 (list 9 9 9))))

(defparameter grid-easy (init-sudoku (list
                                      ; (list 1 1 8)
                                      ; (list 2 1 3)
                                      ; (list 3 1 6)
                                      (list 4 1 9)
                                      (list 5 1 2)
                                      (list 6 1 5)
                                      (list 7 1 7)
                                      (list 8 1 4)
                                      (list 9 1 1)

                                      (list 1 2 2)
                                      (list 2 2 1)
                                      (list 3 2 7)
                                      (list 4 2 8)
                                      (list 5 2 4)
                                      (list 6 2 6)
                                      (list 7 2 9)
                                      (list 8 2 3)
                                      (list 9 2 5)

                                      (list 1 3 5)
                                      (list 2 3 9)
                                      (list 3 3 4)
                                      (list 4 3 7)
                                      (list 5 3 3)
                                      (list 6 3 1)
                                      (list 7 3 2)
                                      (list 8 3 8)
                                      (list 9 3 6)

                                      (list 1 4 3)
                                      (list 2 4 5)
                                      (list 3 4 8)
                                      (list 4 4 1)
                                      (list 5 4 7)
                                      (list 6 4 2)
                                      (list 7 4 6)
                                      (list 8 4 9)
                                      (list 9 4 4)

                                      (list 1 5 1)
                                      (list 2 5 4)
                                      (list 3 5 2)
                                      (list 4 5 6)
                                      (list 5 5 9)
                                      (list 6 5 8)
                                      (list 7 5 5)
                                      (list 8 5 7)
                                      (list 9 5 3)

                                      (list 1 6 7)
                                      (list 2 6 6)
                                      (list 3 6 9)
                                      (list 4 6 3)
                                      (list 5 6 5)
                                      (list 6 6 4)
                                      (list 7 6 1)
                                      (list 8 6 2)
                                      (list 9 6 8)

                                      (list 1 7 4)
                                      (list 2 7 7)
                                      (list 3 7 1)
                                      (list 4 7 5)
                                      (list 5 7 8)
                                      (list 6 7 9)
                                      (list 7 7 3)
                                      (list 8 7 6)
                                      (list 9 7 2)

                                      (list 1 8 6)
                                      (list 2 8 2)
                                      (list 3 8 3)
                                      (list 4 8 4)
                                      (list 5 8 1)
                                      (list 6 8 7)
                                      (list 7 8 8)
                                      (list 8 8 5)
                                      (list 9 8 9)

                                      (list 1 9 9)
                                      (list 2 9 8)
                                      (list 3 9 5)
                                      (list 4 9 2)
                                      (list 5 9 6)
                                      (list 6 9 3)
                                      (list 7 9 4)
                                      (list 8 9 1)
                                      (list 9 9 7))))
