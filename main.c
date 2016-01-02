#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int adj[99][99];
int Max_Size;
int group[99];
int branch[99][99];
int cost[99];
int minimal_branch_count;

void reset_adj();
void read_file();
void output();
void cal();
void sort();
int minimum(int start);
//int group_min(int start);
int main()
{
    reset_adj();
    read_file();
    cal();
    sort();
    output();

    return 0;
}

void reset_adj()
{
    int i,j;
    for(i=0;i<99;i++)
    {
        for(j=0;j<99;j++)
        {
            adj[i][j]=0;
            branch[i][j]=0;
            group[j]=0;
            cost[j]=0;
        }
    }
    minimal_branch_count=0;
}

void read_file()
{
    int i,j;
    FILE *fptr;
    char fname[99];
	printf("Please enter filename(include .txt):");
	scanf("%s",&fname);
    fptr=fopen(fname,"r");
    fscanf(fptr,"%d", &Max_Size);
    for(i=0;i<Max_Size;i++)
    {
        for(j=0;j<Max_Size;j++)
        {
            fscanf(fptr,"%d", &adj[i][j]);

        }
    }
    fclose(fptr);
}

void cal()
{
    int index,min_connect,group_num,j,sub_group,min_connect_target,min_connect_source;
    group_num=1;
    for(index=0;index<Max_Size;index++)
    {
        if(group[index]!=0)
            continue;
        min_connect=minimum(index);
        if(group[min_connect]!=0)
        {
            group[index]=group[min_connect];
        }
        if(group[index]==0&&group[min_connect]==0)
        {
            group[index]=group_num;
            group[min_connect]=group_num;
            group_num++;
        }
    }
    sub_group=group_num;
    group_num=1;
    min_connect=999;
    for(group_num=1;group_num<=sub_group;group_num++)
    {
        for(index=0;index<Max_Size;index++)
        {
            if(group[index]!=group_num)
                continue;
            for(j=0;j<Max_Size;j++)
            {
                if(adj[j][index]>0&&adj[j][index]<min_connect&&group[j]!=group[index])
                {
                    min_connect=adj[j][index];
                    min_connect_target=j;
                    min_connect_source=index;
                }
            }
        }
        //求 聯外minimum edge
        branch[min_connect_target][min_connect_source]=1;
        branch[min_connect_source][min_connect_target]=1;
        //連起來
    }


}

int minimum(int start)
{
    int i,min_val,min_val_index;
    min_val=9999;
    min_val_index=9999;
    for(i=0;i<Max_Size;i++)
    {
        if(adj[i][start]>0&&adj[i][start]<min_val)
        {
            min_val=adj[i][start];
            min_val_index=i;
        }
    }
    branch[min_val_index][start]=1;
    branch[start][min_val_index]=1;
    return min_val_index;
}

void output()
{
    int i,j,print_count;
    print_count=0;
    printf("Minimum cost of Spanning Tree edges in ascending order:\n", );
    while(print_count<minimal_branch_count)
    {
        for(i=0;i<Max_Size;i++)
        {
            for(j=i;j<Max_Size;j++)
            {
                if(branch[i][j]==1&&adj[i][j]==cost[print_count])
                {
                        printf("(%d,%d) = %d\n",i,j,cost[print_count]);
                        print_count++;
                }
            }
        }
    }
}

void sort()
{
    int i,j,k,l,swap;
    for(i=0;i<Max_Size;i++)
    {
        for(j=i;j<Max_Size;j++)
        {
            if(branch[i][j]==1)
            {
                cost[minimal_branch_count]=adj[i][j];
                minimal_branch_count++;
            }
        }
    }
    for(k=0;k<(minimal_branch_count-1);k++)
    {
      for(l=0;l<minimal_branch_count-k-1;l++)
      {
        if (cost[l] > cost[l+1])
        {
          swap       = cost[l];
          cost[l]   = cost[l+1];
          cost[l+1] = swap;
        }
      }
    }

}
