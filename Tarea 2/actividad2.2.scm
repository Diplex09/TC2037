;   Abraham Mendoza A01274857
;   Aldo Degollado
;   Luis Alonso Martínez García A01636255

;1. La funcion insert toma dos entradas: un numero n y una lista lst que contiene numeros en orden ascendente.
;Devuelve una nueva lista con los mismos elementos de lst pero con n insertado en su lugar correspondiente.

 (define (insert n lst)
      (cond
        ((null? lst) (list n))
        ((>= (car lst) n) (cons n lst))
        (else
          (cons (car lst) (insert n (cdr lst))))))