(load "sudoku")

(defparameter grid-impossible (init-sudoku (list
                                            (list 3 1 4)
                                            (list 8 1 7)
                                            (list 1 2 5)
                                            (list 6 2 6)
                                            (list 4 3 5)
                                            (list 9 3 3)
                                            (list 2 4 3)
                                            (list 7 4 7)
                                            (list 5 5 6)
                                            (list 3 6 1)
                                            (list 8 6 2)
                                            (list 1 7 2)
                                            (list 6 7 7)
                                            (list 4 8 2)
                                            (list 9 8 5)
                                            (list 2 9 6)
                                            (list 7 9 2))))


(defparameter grid-evil (init-sudoku (list
                                      (list 3 1 5)
                                      (list 5 1 9)
                                      (list 8 1 6)
                                      (list 2 2 2)
                                      (list 6 2 5)
                                      (list 8 2 1)
                                      (list 1 3 7)
                                      (list 3 3 3)
                                      (list 5 3 8)
                                      (list 1 4 6)
                                      (list 2 4 3)
                                      (list 3 4 8)
                                      (list 2 5 1)
                                      (list 8 5 7)
                                      (list 7 6 3)
                                      (list 8 6 8)
                                      (list 9 6 6)
                                      (list 5 7 2)
                                      (list 7 7 9)
                                      (list 9 7 5)
                                      (list 2 8 5)
                                      (list 4 8 7)
                                      (list 8 8 2)
                                      (list 2 9 6)
                                      (list 5 9 3)
                                      (list 7 9 7))))

(defparameter grid-easy (init-sudoku (list
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

(defparameter grid-trivial (init-sudoku (list
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

(defun main ()
    (format t "~%𝓣𝓻𝓲𝓿𝓲𝓪𝓵 - 𝓘𝓷𝓹𝓾𝓽~%")
    (print-sudoku grid-trivial)
    (format t "~%𝓣𝓻𝓲𝓿𝓲𝓪𝓵 - 𝓢𝓸𝓵𝓿𝓮𝓭~%")
    (print-sudoku (solve-sudoku grid-trivial))
    (format t "~%           ✧✦✧~%~%")
    (format t "~%𝓔𝓪𝓼𝔂 - 𝓘𝓷𝓹𝓾𝓽~%")
    (print-sudoku grid-easy)
    (format t "~%𝓔𝓪𝓼𝔂 - 𝓢𝓸𝓵𝓿𝓮𝓭~%")
    (print-sudoku (solve-sudoku grid-easy))
    (format t "~%           ✧✦✧~%~%")
    (format t "~%𝓔𝓿𝓲𝓵 - 𝓘𝓷𝓹𝓾𝓽~%")
    (print-sudoku grid-evil)
    (format t "~%𝓔𝓿𝓲𝓵 - 𝓢𝓸𝓵𝓿𝓮𝓭~%")
    (print-sudoku (solve-sudoku grid-evil))
    (format t "~%           ✧✦✧~%~%")
    (format t "~%𝓘𝓶𝓹𝓸𝓼𝓼𝓲𝓫𝓵𝓮 - 𝓘𝓷𝓹𝓾𝓽~%")
    (print-sudoku grid-impossible)
    (format t "~%𝓘𝓶𝓹𝓸𝓼𝓼𝓲𝓫𝓵𝓮 - 𝓢𝓸𝓵𝓿𝓮𝓭~%")
    (print-sudoku (solve-sudoku grid-impossible)))

(main)