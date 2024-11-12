import java.util.concurrent.Semaphore;
import java.util.Scanner;

public class RW {
    Semaphore readlock = new Semaphore(1);
    Semaphore writelock = new Semaphore(1);
    static int readcount = 0;

    public class Read implements Runnable {
        @Override
        public void run() {
            try {
                readlock.acquire();
                readcount++;
                if (readcount == 1) {
                    writelock.acquire();
                }
                readlock.release();

                System.out.println("Thread " + Thread.currentThread().getName() + " is reading.");
                Thread.sleep(2500);
                System.out.println("Thread " + Thread.currentThread().getName() + " has finished reading.");

                readcount--;
                readlock.acquire();
                if (readcount == 0) {
                    writelock.release();
                }
                readlock.release();
            } catch (InterruptedException e) {
                System.out.println(e.getMessage());
            }
        }
    }

    public class Write implements Runnable {
        @Override
        public void run() {
            try {
                writelock.acquire();
                System.out.println("Thread " + Thread.currentThread().getName() + " is writing.");
                Thread.sleep(1000);
                System.out.println("Thread " + Thread.currentThread().getName() + " has finished writing.");
                writelock.release();
            } catch (InterruptedException e) {
                System.out.println(e.getMessage());
            }
        }
    }

    void fun() {
        Read read = new Read();
        Write write = new Write();
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the number of read & write processes: ");
        int n = sc.nextInt();
        int seq[] = new int[n];
        System.out.println("Enter the sequence: 1 for reading & 0 for writing.");
        for (int i = 0; i < n; i++) {
            seq[i] = sc.nextInt();
        }

        Thread[] processes = new Thread[n];
        for (int i = 0; i < n; i++) {
            // Ensure that seq[i] is 1 or 0
            if (seq[i] == 1) {
                processes[i] = new Thread(read);
                processes[i].setName("thread " + (i + 1));
            } else if (seq[i] == 0) {
                processes[i] = new Thread(write);
                processes[i].setName("thread " + (i + 1));
            } else {
                // Handle invalid input, if needed
                System.out.println("Invalid sequence value at index " + i);
            }
        }

        // Check for null threads
        for (int i = 0; i < n; i++) {
            if (processes[i] != null) {
                processes[i].start();
            } else {
                System.out.println("Thread " + (i + 1) + " was not created.");
            }
        }

        // Wait for all threads to finish
        for (int i = 0; i < n; i++) {
            try {
                if (processes[i] != null) {
                    processes[i].join(); // Wait for thread to finish
                }
            } catch (InterruptedException e) {
                System.out.println(e.getMessage());
            }
        }
        sc.close();
    }

    public static void main(String args[]) {
        RW rw = new RW();
        rw.fun();
    }
}
