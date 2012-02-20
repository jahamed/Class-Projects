#lang scheme


; note that exp a 0 is always 1. 
; and that exp 3 4 = 3 * (exp 3 3)
; doesn't handle negative values of exp
(define exp
  (lambda (val power product)
    (cond
      [(zero? power) product]
      [else (exp val (- power 1) (* val product))]
      )
    )
  )

(define applyToAll f l)
(exp 2 3 1)