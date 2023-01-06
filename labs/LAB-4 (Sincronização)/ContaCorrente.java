public class ContaCorrente
{
     float saldo = 0;
     float tmp;

public float getSaldo()
{
    return saldo;
}

public void depositar(float valor)
{
     tmp = getSaldo();
     saldo = tmp + valor;
}

public void sacar(float valor)
{
     tmp = getSaldo();
     saldo = tmp - valor;
}
}
