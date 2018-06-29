# Functions

function draw( i){
    graphnum++
    outfile=graphnum ".gv"
    print "  digraph A_" graphnum " { " > outfile
    print "  // graph from left to right" >> outfile
    print "  rankdir=LR;" >> outfile
    print "  splines=true;" >> outfile
    print "#  overlap=true;" >> outfile
    print "  node [shape=box];" >> outfile
    print "  pc [shape=circle, pos=\"3,0!\"]" >> outfile
    print "  sp [shape=circle, pos=\"2,0!\"]" >> outfile

    printf("%s", "stack [shape=record, label=\"") >> outfile
    for(i=0;i<sl;i++) {
	printf("|%s", s[i]) >> outfile
    }
    printf("|<sp>%s",s[sl]) >> outfile
    print "\", pos=\"0,0!\"]" >> outfile
    print "code [shape=record, pos=\"5,0!\", label=\"" code "\"]" >> outfile
    print "pc -> code:c" pc >> outfile
    print "sp -> stack:sp" >> outfile
    if (r1 != "") {
	printf("regs [shape=record, pos=\"2,1!\",label=\"r1 %08x|r2 %08x\"]\n", r1, r2) >> outfile
	}
    print "}" >> outfile
}
function init() {
    sl=1
    s[0]="..."
    code=""
    cp=1
    pc=1
}

#patterns
BEGIN { graphnum=100 ; init() ; }

/^push/ {
    sl++
    s[sl]=$2
    pc++
}

/^pop/ {
    sl--
    pc++
}
/^draw/ { draw() ; }
/^label/ { address[$2]=cp ; code = code "|"; label=$2 ": " }
/^code/ {code=code "|<c" cp ">" label $2 " " $3 " " $4; cp++ ; label=""  }
/^call/ { sl++ ; s[sl] =  pc+8001; pc=address[$2] ; }
/^ret/ { pc=s[sl]-8000 ; sl-- ; }
/^sp\+=/ { sl= sl-$2/4 ;  pc++}
/^sp-=/ { for(i=$2/4;i>0;i--) { sl++ ; s[sl]="???" ; } ; pc++ }
/^read/ { for(x=2;x<=NF;x++) { s[sl+2-x]=$x; draw() ; } pc++}
/^init/ { init() ; }
/^r1=/ { r1=$2; pc++ ;}
/^r2=/ { r2=$2; pc++ ;}
