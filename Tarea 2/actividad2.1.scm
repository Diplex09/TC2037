;   Abraham Mendoza
;   Aldo Degollado
;   Luis Alonso Martínez García A01636255

; 1. La funcion 'fahrenheit-to-celsius' toma como entrada una temperatura f en grados Fahrenheit 
; y la convierte a su equivalente en grados

(define (fahrenheit-to-celsius f)
   (exact->inexact (/ (* 5 (- f 32)) 9))
)

; 2. La funcion 'sign' recibe como entrada un valor entero n. Devuelve -1 si n es negativo, 1 si n es positivo mayor
; que cero, o 0 si n es cero.

(define (sign n) 
    (cond
        ((= n 0) 0)
        ((> n 0) 1)
        ((< n 0) -1)   
    )
)