package multithreading;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author fajar
 */
public class Test extends Thread {
    public static void main(String[] args){
        Test thread1, thread2;
        thread1 = new Test();
        thread2 = new Test();
        thread1.start(); //Will call run.
        thread2.start(); //Will call run.
    }
    
    public void run(){
        int pause;
        for (int i=0; i<10; i++){
            try{
                System.out.println(getName()+" being executed.");
                pause = (int)(Math.random()*3000);
                sleep(pause); //0-3 seconds.
            }
            catch (InterruptedException interruptEx){
                System.out.println(interruptEx);
            }
        }
    }
}
