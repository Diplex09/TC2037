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
    private long resultado;
    
    MiHilo(int id, int ciclos, boolean bandera) {
        this.id = id;
        this.ciclos = ciclos;
        this.bandera = bandera;
    }
    
    @Override
    public void run() {
        System.out.println("START " + id);
        long t1 = System.currentTimeMillis();
        long t2 = System.currentTimeMillis();
        this.resultado = (t2 - t1);
    }
    
    public long getResultado()
    {
        return this.resultado;
    }
    
    public void detener() {
        this.bandera = false;
    }
}
