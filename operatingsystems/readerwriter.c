#include <semaphore.h>

int main()
{
    semaphore s;
    int i;

    // Initialize the semaphore.
    sem_init(&s, 0, 1);

    // Create a number of reader and writer threads.
    for (i = 0; i < 10; i++)
    {
        if (i % 2 == 0)
        {
            // Create a reader thread.
            pthread_t reader;
            pthread_create(&reader, NULL, reader_function, &s);
        }
        else
        {
            // Create a writer thread.
            pthread_t writer;
            pthread_create(&writer, NULL, writer_function, &s);
        }
    }

    // Wait for all of the threads to finish.
    for (i = 0; i < 10; i++)
    {
        pthread_join(reader, NULL);
        pthread_join(writer, NULL);
    }

    // Destroy the semaphore.
    sem_destroy(&s);

    return 0;
}

void reader_function(void *arg)
{
    semaphore *s = (semaphore *)arg;

    // Acquire the semaphore.
    sem_wait(s);

    // Read from the shared resource.

    // Release the semaphore.
    sem_post(s);
}

void writer_function(void *arg)
{
    semaphore *s = (semaphore *)arg;

    // Acquire the semaphore.
    sem_wait(s);

    // Write to the shared resource.

    // Release the semaphore.
    sem_post(s);
}