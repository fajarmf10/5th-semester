/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package multithreading;

/**
 *
 * @author fajar
 */
public class HelloClass {
    public static void main(String[] args){
        HelloThread hello = new HelloThread();
        CountThread count = new CountThread();
        hello.start();
        count.start();
    }
}

class HelloThread extends Thread {
    public void run(){
        int pause;
        for(int i=0; i<5; i++){
            try{
                System.out.println("Hello!");
                pause = (int) (Math.random() * 3000);
                
                sleep(pause);
            }
            catch(InterruptedException iEx){
                System.out.println(iEx);
            }
        }
    }
}

class CountThread extends Thread {
    public void run(){
        int pause;
        for(int i=0; i<5; i++){
            try{
                System.out.println(i);
                pause = (int) (Math.random() * 3000);
                
                sleep(pause);
            }
            catch(InterruptedException iEx){
                System.out.println(iEx);
            }
        }
    }
}