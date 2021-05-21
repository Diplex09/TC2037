/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author aldo, abraham, alonso 
 */
public class MiHilo extends Thread {
    int id;
    int ciclos;
    boolean bandera;
    int firstNum;
    int lastNum;
    private long resultado;
    
    MiHilo(int id, int ciclos, boolean bandera, int firstNum, int lastNum) {
        this.id = id;
        this.ciclos = ciclos;
        this.bandera = bandera;
        this.firstNum = firstNum;
        this.lastNum = lastNum;
    }
    
    private boolean numberIsPrime(int num) {
        if(num < 2) {
            return false;
        }
        else {
            boolean numIsPrime = true;
            for(int i=2; i <= Math.sqrt(num); i++) {
                if(num % i == 0) {
                    numIsPrime = false;
                    break;
                }
            }
            return numIsPrime;
        }
    }
    
    @Override
    public void run() {
        System.out.println("Hilo " + id + " empieza");
        for(int i=this.firstNum; i < this.lastNum; i++){
            if(numberIsPrime(i)){
                this.resultado += i;
            }
        }
    }
    
    public long getResultado()
    {
        return this.resultado;
    }
    
    public void detener() {
        this.bandera = false;
    }
}
