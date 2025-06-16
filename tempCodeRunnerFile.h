 FILE *fp;
        Prestador aux;
        int returnAlta;
        int auxDNI = 0;
        float costoDespreciado = 0.0;

        if ((fp = fopen("Prestadores.txt", "r")) == NULL)
        {
            return 3;
        }

        fseek(fp, 0, SEEK_END); //(fichero, desplazamiento, origen) , SEEK_END el desplazamiento se cuenta desde el final del archivo
        if (ftell(fp) == 0)     // indica la posicion actual en un archivo
        {
            return 2;
        }

        rewind(fp);

        while (lista->ultimo < MAX - 1 && !(feof(fp)))
        {
            fscanf(fp, "%d\n", &auxDNI);

            if (aux.dni < 10000000 || aux.dni > INFINITO)
            {
                for (int i = 0; i < 5; i++)
                {
                    fscanf(fp, "%*[^\n]\n");
                    if (feof(fp))
                    {
                        break; // Salir del bucle si llegamos al final del archivo
                    }
                }
            }

            getchar();
            aux.dni = auxDNI;
            fgets(aux.nombre, sizeof(aux.nombre), fp);
            aux.nombre[strcspn(aux.nombre, "\n")] = '\0'; // Elimina el \n
            fgets(aux.servicios, sizeof(aux.servicios), fp);
            aux.servicios[strcspn(aux.servicios, "\n")] = '\0';
            fgets(aux.domicilio, sizeof(aux.domicilio), fp);
            aux.domicilio[strcspn(aux.domicilio, "\n")] = '\0';
            fgets(aux.email, sizeof(aux.email), fp);
            aux.email[strcspn(aux.email, "\n")] = '\0';
            fgets(aux.telefono, sizeof(aux.telefono), fp);
            aux.telefono[strcspn(aux.telefono, "\n")] = '\0';


                returnAlta = altaLIBB(aux, lista, &costoDespreciado);
                if (!returnAlta)
                {
                    printf("Ya existe un prestador asociado al dni %d en la estructura.\n", aux.dni);
                }
            
        }
        getchar();
        fclose(fp);
        return (lista->ultimo == MAX - 1) ? 4 : 1;