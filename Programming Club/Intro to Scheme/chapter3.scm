#lang scheme

(define rember
  (lambda (a lat)
    (cond
      ((null? lat) ('()))
      ((eq? (car lat) a) (cdr lat))
      (else (cons (car lat) (rember a (cdr lat)))))))

(define firsts
  (lambda (l)
    (cond
      ((null? l) '())
      (else (cons (car (car l)) (firsts (cdr l)))))))

(rember 'hello '(hi hello goodbye))
(firsts '((a b) (c d)))