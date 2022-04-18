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
  "Test whether the number at the given coordinates makes sense
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
  "Initialize a new sudoku grid

  Provide transformations as arguments in the form as a list of lists
  containing 3 numbers, the x coordinate, the y coordinate, and the number to
  put in that cell. The coordinates should be 1 indexed.
  "
  (let ((sudoku (make-list 81)))
    (loop for transform in transforms
      do (
          setf (nth (indx? (- (first transform) 1) (- (second transform) 1)) sudoku) (third transform)))
   sudoku))

(defun solve-sudoku (grid &optional ( depth 0))
  "Solve the given sudoku grid
  "
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
               ; (screen:with-window (screen:clear-window screen:*window*))
               ; (print-sudoku new-grid)
               ; (format t "~% x = ~d y = ~d i = ~2d ~%" x y i)
               ; (format t "~% depth = ~d ~%" depth)
               (if (choice-valid? x y new-grid)
                   (let ((computed (solve-sudoku new-grid (+ depth 1))))
                       (if computed
                         (return-from solve-sudoku computed)))))))))

(defun print-sudoku (grid)
  "Pretty print the sudoku grid
  "
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
  

