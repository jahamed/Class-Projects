#lang scheme

(define atom?
  (lambda (x)
    (and (not(pair? x))(not (null? x)))))

;; returns true if the list paramter is a list of atoms only
(define lat?
  (lambda (l)
    (cond
      ((null? l) #t)
      ((atom? (car l)) (lat? (cdr l)))
      (else #f))))

;; returns true if the atom a is contained in the list lat
(define member?
  (lambda (a lat)
    (cond 
      ((null? lat) #f)
      (else (or (eq? (car lat) a) (member? a (cdr lat)))))))

;; call lambdas here
(car '(bacon eggs))
(cdr '(bacon and (eggs)))
(lat? '(bacon and eggs))
(or (atom? '(hello)) (null? '(lol)))
(member? 'hello '(bye hi hello))
(car '(bacon eggs))