enum s_tok
{
	WORD,
	HRD,
	RIN,
	ROU,
	APP,
	PIPE,
};


struct file
{
	char *s;
	s_tok tok;
	struct file *next;
};


int main()
{
	file a;
	a.s = "echo";
	a.tok = WORD;
	a.next->s = "hello | < > <world";
	a.next->tok = WORD;
	a.next->next->s = ">";
	a.next->next->tok = ROU;

}