#include <stdio.h>
#include <stdlib.h>

typedef struct tree
{
    int x;        //x-coordinate
    int y;        //y-coordinate
    int h;        //height
    int d;        //thickness
    int c;        //unit weight
    int p;        //unit value
    int tp;       //tree presence
    int value;    //total value
    int weight;   //total weight
    int distance;
} grid;

int l,time;

void distance(grid **g,int n,int *I,int *J,int *X,int *Y)
{
    int i,j,min=n*n;
    *X=*I;
    *Y=*J;
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            if(g[i][j].distance>0)
            {
                g[i][j].distance=((i-*I)*(i-*I))+((j-*J)*(j-*J));
            }
        }
    }
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            if(g[i][j].distance<=min && g[i][j].distance>0)
            {
                min=g[i][j].distance;
                *I=i;
                *J=j;
            }
        }
    }
}

void print(int i,int j,int x,int y)
{
    while(i<x)
    {
        if(time>0)
        {
            printf("move right\n");
            time=time-1;
            i++;
        }
        else
        {
            break;
        }
    }
    while(j<y)
    {
        if(time>0)
        {
            printf("move up\n");
            time=time-1;
            j++;
        }
        else
        {
            break;
        }
    }
    while(i>x)
    {
        if(time>0)
        {
            printf("move left\n");
            time=time-1;
            i--;
        }
        else
        {
            break;
        }
    }
    while(j>y)
    {
        if(time>0)
        {
            printf("move down\n");
            time=time-1;
            j--;
        }
        else
        {
            break;
        }
    }
}

void calc(grid **g,int x,int y,int i,int n)
{
    int j=1;
    while(g[x][y].h>=j)
    {
        if(i==1 && x+j<n)
        {
            if(g[x+j][y].tp==1 && g[x][y].weight<=g[x+j][y].weight)
            {
                break;
            }
            if(g[x+j][y].tp==1 && g[x][y].weight>g[x+j][y].weight)
            {
                g[x+j][y].tp=0;
                g[x+j][y].distance=0;
                l=l-1;
                calc(g,x+j,y,1,n);
            }
        }
        else if(i==2 && y+j<n)
        {
            if(g[x][y+j].tp==1 && g[x][y].weight<=g[x][y+j].weight)
            {
                break;
            }
            if(g[x][y+j].tp==1 && g[x][y].weight>g[x][y+j].weight)
            {
                g[x][y+j].tp=0;
                g[x][y+j].distance=0;
                l=l-1;
                calc(g,x,y+j,2,n);
            }
        }
        else if(i==3 && x-j>0)
        {
            if(g[x-j][y].tp==1 && g[x][y].weight<=g[x-j][y].weight)
            {
                break;
            }
            if(g[x-j][y].tp==1 && g[x][y].weight>g[x-j][y].weight)
            {
                g[x-j][y].tp=0;
                g[x-j][y].distance=0;
                l=l-1;
                calc(g,x-j,y,3,n);
            }
        }
        else if(i==4 && y-j>0)
        {
            if(g[x][y-j].tp==1 && g[x][y].weight<=g[x][y-j].weight)
            {
                break;
            }
            if(g[x][y-j].tp==1 && g[x][y].weight>g[x][y-j].weight)
            {
                g[x][y-j].tp=0;
                g[x][y-j].distance=0;
                l=l-1;
                calc(g,x,y-j,4,n);
            }
        }
        j++;
    }
}

void calculation(grid **g,int x,int y,int n)
{
    int j=1;
    while(g[x][y].h>=j)
    {
        if(x+j<n)
        {
            if(g[x+j][y].tp==1 && g[x][y].weight>g[x+j][y].weight)
            {
                if(time>=g[x][y].d)
                {
                    printf("cut right\n");
                    time=time-g[x][y].d;
                    l=l-2;
                    g[x+j][y].distance=0;
                    g[x][y].distance=0;
                    g[x+j][y].tp=0;
                    g[x][y].tp=0;
                    calc(g,x+j,y,1,n);
                    return;
                }
                else
                {
                    return;
                }
            }
        }
        if(y+j<n)
        {
            if(g[x][y+j].tp==1 && g[x][y].weight>g[x][y+j].weight)
            {
                if(time>=g[x][y].d)
                {
                    printf("cut up\n");
                    time=time-g[x][y].d;
                    l=l-2;
                    g[x][y+j].distance=0;
                    g[x][y].distance=0;
                    g[x][y+j].tp=0;
                    g[x][y].tp=0;
                    calc(g,x,y+j,2,n);
                    return;
                }
                else
                {
                    return;
                }
            }
        }
        if(x-j>=0)
        {
            if(g[x-j][y].tp==1 && g[x][y].weight>g[x-j][y].weight)
            {
                if(time>=g[x][y].d)
                {
                    printf("cut left\n");
                    time=time-g[x][y].d;
                    l=l-2;
                    g[x-j][y].distance=0;
                    g[x][y].distance=0;
                    g[x-j][y].tp=0;
                    g[x][y].tp=0;
                    calc(g,x-j,y,3,n);
                    return;
                }
                else
                {
                    return;
                }
            }
        }
        if(y-j>=0)
        {
            if(g[x][y-j].tp==1 && g[x][y].weight>g[x][y-j].weight)
            {
                if(time>=g[x][y].d)
                {
                    printf("cut down\n");
                    time=time-g[x][y].d;
                    l=l-2;
                    g[x][y-j].distance=0;
                    g[x][y].distance=0;
                    g[x][y-j].tp=0;
                    g[x][y].tp=0;
                    calc(g,x,y-j,4,n);
                    return;
                }
                else
                {
                    return;
                }
            }
        }
        j++;
    }
    if(time>=g[x][y].d)
    {
        g[x][y].tp=0;
        g[x][y].distance=0;
        l=l-1;
        printf("cut up\n");
        time=time-g[x][y].d;
    }
}

int main()
{
    int i;
    int j;
    int t;
    int n;
    int k;
    int x;
    int y;
    scanf("%d",&t);
    scanf("%d",&n);
    scanf("%d",&k);
    grid **g;
    g = (grid **)malloc(sizeof(grid *) * n);
    for (i = 0; i < n; i++)
    {
        g[i] = (grid *)malloc(sizeof(grid) * n);
    }
    l=k;
    time=t;
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            g[i][j].x=i;
            g[i][j].y=j;
            g[i][j].h=0;
            g[i][j].d=0;
            g[i][j].c=0;
            g[i][j].p=0;
            g[i][j].tp=0;
            g[i][j].value=0;
            g[i][j].weight=0;
            g[i][j].distance=0;
        }
    }
    for(i=0; i<k; i++)
    {
        scanf("%d",&x);
        scanf("%d",&y);
        scanf("%d",&g[x][y].h);
        scanf("%d",&g[x][y].d);
        scanf("%d",&g[x][y].c);
        scanf("%d",&g[x][y].p);
        g[x][y].distance=(x*x)+(y*y);
        g[x][y].x=x;
        g[x][y].y=y;
        g[x][y].tp=1;
        g[x][y].value=g[x][y].p*g[x][y].h*g[x][y].d;
        g[x][y].weight=g[x][y].c*g[x][y].d*g[x][y].h;
        if(g[x][y].distance==0)
        {
            g[x][y].tp=0;
            g[x][y].value=0;
            g[x][y].weight=0;
            g[x][y].distance=0;
            l=l-1;
        }
    }
    int I=0,J=0;
    int X,Y;
    while(l>0)
    {
        if(time>0)
        {
            distance(g,n,&I,&J,&X,&Y);
            if(time>0)
            {
                print(X,Y,I,J);
            }
            else
            {
                break;
            }
            if(time>0)
            {
                calculation(g,I,J,n);
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
}
