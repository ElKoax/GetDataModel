int GDM;

typedef DWORD(__cdecl* gdm2)();
gdm2 getdatamodel2 = (gdm2)(ASLR(0xE4A530));


typedef DWORD(__thiscall* getdatamodel)(DWORD, DWORD);
getdatamodel r_getdatamodel = (getdatamodel)(ASLR(0xE4A680));

int GetDatamodel()
{
	DWORD DMPad[2]{};
	r_getdatamodel(getdatamodel2(), (DWORD)DMPad);
	DWORD DM = DMPad[0];
	return DM + 0x44;
	/*
	GetDataModel, Fixed by Shade and Synapse X source code i guess? xD enjoy this.
	*/
}

const char* GetClass(int self)
{
	return (const char*)(*(int(**)(void))(*(int*)self + 16))();
}

int FindFirstClass(int Instance, const char* Name)
{
	DWORD StartOfChildren = *(DWORD*)(Instance + 0x2C);
	DWORD EndOfChildren = *(DWORD*)(StartOfChildren + 4);

	for (int i = *(int*)StartOfChildren; i != EndOfChildren; i += 8)
	{
		if (memcmp(GetClass(*(int*)i), Name, strlen(Name)) == 0)
		{
			return *(int*)i;
		}
	}
}



void getdatamodelaaa()
{
	GDM = GetDatamodel();
	ScriptContext = FindFirstClass(GDM, "ScriptContext");
	r_L = *(DWORD*)(ScriptContext + 56 * 0 + 164) - (ScriptContext + 56 * 0 + 164); // if ur going to use this for AXON, change "r_L" to m_rL
	*(DWORD*)(*(DWORD*)(r_L + 112) + 24) = 6;
	printf("Passed GetDataModel, Enjoy Exploiting! \n");
}
