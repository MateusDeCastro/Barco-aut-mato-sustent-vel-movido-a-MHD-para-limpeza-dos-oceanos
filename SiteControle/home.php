<!DOCTYPE html>
<html lang="pt-br">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Home</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet"
        integrity="sha384-QWTKZyjpPEjISv5WaRU9OFeRpok6YctnYmDr5pNlyT2bRjXh0JMhjY6hW+ALEwIH" crossorigin="anonymous">
</head>

<body style="background-color: #ddeff9">
    <nav class="navbar navbar-expand fs-2" style="background-color: black;">
        <div class="container text-center">
            <ul class="navbar-nav">
                <li class="nav-item">
                    <a class="btn btn-outline-light fs-3" href="#section1">Controle</a>
                </li>
            </ul>
            <ul class="navbar-nav">
                <li class="nav-item">
                    <a class="btn btn-outline-light fs-3" href="#section2">Trajetos</a>
                </li>
            </ul>
            <ul class="navbar-nav">
                <li class="nav-item">
                    <a class="btn btn-outline-light fs-3" href="menu.html">Voltar para menu</a>
                </li>
            </ul>
        </div>
    </nav>
    <section id="section1">
        <div class="container text-center pt-5">
            <form>
                <div class="id-barco pt-3">
                    <h4>Digite o ID do barco: </h4>
                    <input class="pb-1" placeholder="Digite o ID" type="text" name="selecao-id-barco">
                </div>
                <div class="mapa mt-3">
                    <div class="localfinal">
                        <h3>Localização Atual</h3>
                    </div>
                    <iframe class="border border-primary"
                        src="https://www.google.com/maps/embed?pb=!1m18!1m12!1m3!1d3678.8513362494646!2d-47.158877724572804!3d-22.770897733028946!2m3!1f0!2f0!3f0!3m2!1i1024!2i768!4f13.1!3m3!1m2!1s0x94c8bfdfadff4025%3A0xfa3a1732028d3ec9!2sCentro%20Municipal%20de%20Educa%C3%A7%C3%A3o%20Profissional%20Osmar%20Passarelli%20Silveira!5e0!3m2!1spt-BR!2sbr!4v1723243478554!5m2!1spt-BR!2sbr"
                        width="600" height="450" style="border:0;" allowfullscreen="" loading="lazy"
                        referrerpolicy="no-referrer-when-downgrade"></iframe>
                </div>
                <div class="id-barco pt-3">
                    <h4>Localização final: </h4>
                    <input class="pb-1" placeholder="Digite a localização final" type="text" name="localidade-final">
                </div>
                <div class="mt-auto text-center pt-3">
                    <button type="submit" class="btn btn-outline-dark">Enviar</button>
                </div>
            </form>
        </div>
    </section>
    <div class="container-fluid text-center pt-4">
        <h2>Controle manual</h2>
        <div class="container-fluid text-center pt-3">
        <button type="button" class="btn btn-primary">Esquerda</button>
        <button type="button" class="btn btn-primary">Linha reta</button>
        <button type="button" class="btn btn-primary">Direita</button>

        </div>
    </div>
    <section id="section2">
        <div class="container-fluid text-center pt-5">
            <h2 class="text-center pb-5">Trajetos Finalizados</h2>
            <div class="container text-center mb-5">
                <div class="row pb-2">
                    <div class="col fw-bold fs-5">ID</div>
                    <div class="col fw-bold fs-5">Hora da saída</div>
                    <div class="col fw-bold fs-5">Hora da chegada</div>
                    <div class="col fw-bold fs-5">Data da saída</div>
                    <div class="col fw-bold fs-5">Data da chegada</div>
                    <div class="col fw-bold fs-5">Local da saída</div>
                    <div class="col fw-bold fs-5">Local da chegada</div>
                    <div class="col fw-bold fs-5">Status</div>
                </div>
                <?php
                require_once("class/database.class.php");

                try {
                    $con = new Database();
                    $link = $con->getConexao();

                    // Prepara a consulta SQL
                    $stmt = $link->prepare("SELECT * FROM dados");

                    // Executa a consulta SQL
                    $stmt->execute();

                    // Itera sobre os resultados um por um
                    while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
                        echo '<div class="row pb-2">';
                        echo '<div class="col">' . htmlspecialchars($row['id']) . '</div>';
                        echo '<div class="col">' . htmlspecialchars($row['hora_saida']) . '</div>';
                        echo '<div class="col">' . htmlspecialchars($row['hora_chegada']) . '</div>';
                        echo '<div class="col">' . htmlspecialchars($row['data_saida']) . '</div>';
                        echo '<div class="col">' . htmlspecialchars($row['data_chegada']) . '</div>';
                        echo '<div class="col">' . htmlspecialchars($row['local_saida']) . '</div>';
                        echo '<div class="col">' . htmlspecialchars($row['local_chegada']) . '</div>';
                        echo '<div class="col">' . htmlspecialchars($row['status']) . '</div>';
                        echo '</div>';
                    }

                } catch (PDOException $e) {
                    // Trata erros de banco de dados
                    echo '<div class="text-danger">Erro no banco de dados: ' . htmlspecialchars($e->getMessage()) . '</div>';
                } catch (Exception $e) {
                    // Trata outros tipos de erros
                    echo '<div class="text-danger">Erro geral: ' . htmlspecialchars($e->getMessage()) . '</div>';
                }
                ?>
            </div>
        </div>
    </section>
    <footer class="container-fluid bg-muted text-center pt-3">
        <div class="container text-center">
            <div class="row">
                <div class="col">
                    Desenvolvedores
                </div>
            </div>
            <div class="row">
                <div class="col">
                    Guilherme Henrique Moreira
                </div>
                <div class="col">
                    Mateus de Castro Farah Aranha
                </div>
                <div class="col">
                    Felipe Dalan do Passos
                </div>
            </div>
            <div class="row">
                <div class="col">
                    guilherme.moreira@alu.paulinia.sp.gov.br
                </div>
                <div class="col">
                    mateus.aranha@alu.paulinia.sp.gov.br
                </div>
                <div class="col">
                    felipe.passos@alu.paulinia.sp.gov.br
                </div>
            </div>
        </div>
    </footer>
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js"
        integrity="sha384-YvpcrYf0tY3lHB60NNkmXc5s9fDVZLESaAA55NDzOxhy9GkcIdslK1eN7N6jIeHz"
        crossorigin="anonymous"></script>
</body>

</html>