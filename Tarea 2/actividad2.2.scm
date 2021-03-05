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

; 6. La funcion deep-reverse toma una lista como entrada. Devuelve una lista con los mismos elementos que su
; entrada pero en orden inverso. Si hay listas anidadas, estas tambien se invierten.

(define (deep-reverse lst)
    (define (deep-reverseR lst acc)
        (if (null? lst)
            acc
            (if (list? (car lst))
                (deep-reverseR (cdr lst) (cons (deep-reverse (car lst)) acc))
                (deep-reverseR (cdr lst) (cons (car lst) acc))
            )
        )
    )
   (deep-reverseR lst '())
)