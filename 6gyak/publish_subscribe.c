#include <stdlib.h>
#include <string.h>

typedef struct Topic
{
    char *name;
    int num_posts;
    float avg_rating;
} Topic;

Topic *create_topic(char *name)
{
    Topic *topic = malloc(sizeof(Topic));
    topic->name = malloc(strlen(name) + 1);
    strcpy(topic->name, name);
    topic->num_posts = 0;
    topic->avg_rating = 0.0;
    return topic;
}

void add_post(Topic *topic, float rating)
{
    float sum_ratings = topic->avg_rating * topic->num_posts;
    sum_ratings += rating;
    topic->num_posts++;
    topic->avg_rating = sum_ratings / topic->num_posts;
}

void delete_topic(Topic *topic)
{
    free(topic->name);
    free(topic);
}
